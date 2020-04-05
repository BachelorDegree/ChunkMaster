#include <cmath>
#include <vector>
#include <spdlog/spdlog.h>

#include "IdAllocatorServiceClient/IdAllocatorServiceClient.hpp"

#include "errcode.h"
#include "Logic/SQLite.hpp"
#include "AllocateUploadSlicesHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

void AllocateUploadSlicesHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.AllocateUploadSlices";
}

void AllocateUploadSlicesHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestAllocateUploadSlices(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new AllocateUploadSlicesHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        // int iRet = ChunkMasterServiceImpl::GetInstance()->AllocateUploadSlices(request, response);
        int iRet = this->Implementation();
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

void CalculateSlicesLength(uint64_t iDataLength, std::vector<uint32_t> &outLengths)
{
    /* 分片策略：16 MiB 以下直接按 4K 向上取整对齐
    16 MiB 以上，128 MiB 以下的按 16 MiB 一片
    128 MiB 以上的，按 128 MiB 一片 */
    constexpr uint64_t MiB_16 = 16 * 1024 * 1024;
    constexpr uint64_t MiB_128 = 128 * 1024 * 1024;
    if (iDataLength <= MiB_16)
    {
        outLengths.emplace_back(iDataLength);
        return;
    }
    if (iDataLength >= MiB_128)
    {
        auto iCount128 = iDataLength / MiB_128;
        outLengths.reserve(iCount128 + 1);
        for (decltype(iCount128) i = 0; i < iCount128; ++i)
            outLengths.emplace_back(MiB_128);
        outLengths.emplace_back(iDataLength - MiB_128 * iCount128);
        return;
    }
    // 16 < iDataLength < 128
    auto iCount16 = iDataLength / MiB_16;
    outLengths.reserve(iCount16 + 1);
    for (decltype(iCount16) i = 0; i < iCount16; ++i)
        outLengths.emplace_back(MiB_16);
    outLengths.emplace_back(iDataLength - MiB_16 * iCount16);
}

int AllocateUploadSlicesHandler::Implementation(void)
{
    constexpr auto iChunkDataSectionOffset = 16781312;
    constexpr auto iChunkDataSectionLength = 2 * 1024 * 1024 * 1024 - iChunkDataSectionOffset;
    int iRet = 0;
    auto iDataLength = request.data_length();
    auto iReplicaCount = request.replica_policy();

    // 计算各个分片的逻辑长度
    std::vector<uint32_t> vecLengths;
    CalculateSlicesLength(iDataLength, vecLengths);

    // RPC 拉逻辑ID
    ::idallocator::BatchAllocateIdResp oBatchAllocateIdRsp;
    do
    {
        IdAllocatorServiceClient oClient;
        ::idallocator::BatchAllocateIdReq oBatchAllocateIdReq;
        oBatchAllocateIdReq.set_count(vecLengths.size());
        auto iAllocateIdRet = oClient.BatchAllocateId(oBatchAllocateIdReq, oBatchAllocateIdRsp);
        if (iAllocateIdRet != 0)
        {
            spdlog::error("Batch allocated logical ID failed, retcode={}", iAllocateIdRet);
            return E_ALLOCATE_LOGICAL_SLICE_ID_RPC_FAILED;
        }
    } while (false);

    // SQLite 找物理chunk
    // 条件：chunk状态为STANDBY、不在同一machine、实际剩余空间大于等于ceil4k后的分片大小
    for (const auto iSliceLogicalLength : vecLengths)
    {
        auto iMaximumActualUsed = iChunkDataSectionLength - Ceil4K(iSliceLogicalLength);
        std::string sSql = fmt::format("SELECT chunk_id, actual_used FROM chunks WHERE state=0 AND actual_used<{} GROUP BY cluster_id, machine_id, disk_id ORDER BY actual_used ASC;", iMaximumActualUsed);
        SQLite::Statement oStmt(*g_pSqliteDatabase, sSql);
        
    }

    return iRet;
}
