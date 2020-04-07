#include <cmath>
#include <vector>
#include <spdlog/spdlog.h>
#include "coredeps/SliceId.hpp"

#include "IdAllocatorServiceClient/IdAllocatorServiceClient.hpp"
#include "ChunkServerServiceClient/ChunkServerServiceClient.hpp"

#include "errcode.h"
#include "Logic/Global.hpp"
#include "Logic/SQLite.hpp"
#include "Logic/ChunkFSM.hpp"
#include "Logic/SliceIndexKVHelper.hpp"

#include "AllocateUploadSliceHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

void AllocateUploadSliceHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.AllocateUploadSlice";
}

void AllocateUploadSliceHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestAllocateUploadSlice(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new AllocateUploadSliceHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        // int iRet = ChunkMasterServiceImpl::GetInstance()->AllocateUploadSlice(request, response);
        auto iRet = this->Implementation();
        this->SetReturnCode(iRet);
        this->SetStatusFinish();
        responder.Finish(response, grpc::Status::OK, this);
        break;
    }
    case Status::FINISH:
        delete this;
        break;
    default:
        // throw exception
        ;
    }
}

inline uint32_t Ceil4K(uint32_t iSize)
{
    constexpr uint32_t KiB_4 = 4 * 1024;
    return static_cast<uint32_t>(ceil((iSize / static_cast<double>(KiB_4))) * KiB_4);
}

int AllocateUploadSliceHandler::Implementation(void)
{
    int iRet = 0;
    auto iSliceLength = request.data_length();
    auto iReplicaCount = request.replica_policy();
    constexpr auto iChunkDataSectionOffset = 16781312;
    constexpr auto iChunkDataSectionLength = 2UL * 1024 * 1024 * 1024 - iChunkDataSectionOffset;

    // RPC 拉逻辑ID
    do
    {
        IdAllocatorServiceClient oClient;
        ::idallocator::AllocateIdReq oAllocateIdReq;
        ::idallocator::AllocateIdResp oAllocateIdRsp;
        auto iAllocateIdRet = oClient.AllocateId(oAllocateIdReq, oAllocateIdRsp);
        if (iAllocateIdRet != 0)
        {
            spdlog::error("AllocateUploadSlice - Allocate logical ID failed, retcode={}", iAllocateIdRet);
            return E_IDALLOCATOR_ALLOCATE_ID_RPC_FAILED;
        }
        response.set_logical_slice_id(oAllocateIdRsp.id());
    } while (false);
    auto iLSID = response.logical_slice_id();

    do
    {
        std::lock_guard<libco::CoMutex> guard(*g_pMutexAllChunk); // 注意这个guard的生命周期
        auto iMaximumActualUsed = iChunkDataSectionLength - Ceil4K(iSliceLength);

        // SQLite 找物理chunk
        // 条件：chunk状态为STANDBY、不在同一machine、实际剩余空间大于等于ceil4k后的分片大小
        std::vector<uint64_t> vecChunks;
        std::string sSql = fmt::format("SELECT chunk_id, actual_used FROM chunks WHERE state=0 AND actual_used<{} GROUP BY cluster_id, machine_id, disk_id ORDER BY actual_used ASC;", iMaximumActualUsed);
        SQLite::Statement oStmt(*g_pSqliteDatabase, sSql);
        spdlog::trace(sSql);
        while (oStmt.executeStep())
        {
            vecChunks.emplace_back(static_cast<uint64_t>(oStmt.getColumn(0).getInt64()));
            if (vecChunks.size() >= iReplicaCount)
                break;
        }
        if (vecChunks.size() < iReplicaCount) // 找不到足够多的chunk来存放副本
        {
            spdlog::warn("AllocateUploadSlice - Insufficient chunk replica! Slice length: {}", iSliceLength);
            return E_INSUFFICIENT_CHUNK_REPLICA;
        }

        // 挨个分配inode并SQL标记
        try
        {
            SQLite::Transaction oTransaction(*g_pSqliteDatabase);
            ::chunkserver::AllocateInodeReq oReq;
            ::chunkserver::AllocateInodeRsp oRsp;
            oReq.set_data_length(iSliceLength);
            for (const auto iChunkId: vecChunks)
            {
                Storage::SliceId oChunkId(iChunkId);
                ChunkServerServiceClient oClient(CanonicalChunkServerName(iChunkId));
                oReq.set_chunk_id(iChunkId);
                auto iAllocateInodeRet = oClient.AllocateInode(oReq, oRsp);
                if (iAllocateInodeRet != 0)
                {
                    spdlog::error("AllocateUploadSlice - ChunkServer allocate inode error, chunk_id: 0x{:016x}, retcode: {}", iChunkId, iAllocateInodeRet);
                    return E_CHUNKSERVER_ALLOCATE_INODE_RPC_FAILED;
                }
                response.add_physical_slice_id(oRsp.slice_id());
                auto sSql = fmt::format("UPDATE chunks SET logical_used=logical_used+{}, actual_used=actual_used+{}, state={} WHERE chunk_id={};", 
                    iSliceLength, Ceil4K(iSliceLength), static_cast<int>(ChunkFSM::WRITING), oChunkId.UInt());
                spdlog::trace(sSql);
                int iExecRet = g_pSqliteDatabase->exec(sSql);
                if (iExecRet != 1) // affected row count
                {
                    spdlog::error("AllocateUploadSlice - SQLite UPDATE failed, SQL: {}", sSql);
                    return E_SQLITE_UPDATE_FAILED;
                }
            }
            oTransaction.commit();
        }
        catch(const SQLite::Exception& e)
        {
            spdlog::error("AllocateUploadSlice - SQLite exception: {}", e.getErrorStr());
            return E_SQLITE_EXCEPTION_CAUGHT;
        }
    } while (false);
    spdlog::trace("AllocateUploadSlice - Rsp debug string: {}", response.ShortDebugString());
    
    // 把 SliceIdx 落 KV
    std::vector<uint64_t> vecPhysicalIds;
    for (auto i = 0; i < response.physical_slice_id_size(); ++i)
        vecPhysicalIds.emplace_back(response.physical_slice_id(i));
    iRet = SliceIndexKVHelper::SetMapping(iLSID, vecPhysicalIds);

    return iRet;
}
