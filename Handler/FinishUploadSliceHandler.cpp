#include <spdlog/spdlog.h>
#include "coredeps/SliceId.hpp"

#include "ChunkServerServiceClient/ChunkServerServiceClient.hpp"

#include "errcode.h"
#include "Logic/SQLite.hpp"
#include "Logic/ChunkFSM.hpp"

#include "FinishUploadSliceHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

void FinishUploadSliceHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.FinishUploadSlice";
}

void FinishUploadSliceHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestFinishUploadSlice(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new FinishUploadSliceHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        // int iRet = ChunkMasterServiceImpl::GetInstance()->FinishUploadSlice(request, response);
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

int FinishUploadSliceHandler::Implementation(void)
{
    int iRet = 0;
    // 对应的chunk 状态转移
    Storage::SliceId oPsid(request.physical_slice_id());
    Storage::SliceId oChunkId(request.physical_slice_id());
    oChunkId.SetSlice(0);
    
    // 查当前状态
    uint32_t iCurrentState = ChunkFSM::NOTKNOWN;
    do
    {
        auto sSql = fmt::format("SELECT state FROM chunks WHERE chunk_id={};", oChunkId.UInt());
        spdlog::trace(sSql);
        SQLite::Statement oStatement(*g_pSqliteDatabase, sSql);
        bool bIsExecSuccess;
        try
        {
            bIsExecSuccess = oStatement.executeStep();
        }
        catch(const SQLite::Exception& e)
        {
            spdlog::error("FinishUploadSliceHandler SELECT FAILED: SQL={}, ERRMSG={}", sSql, e.getErrorStr());
            return E_SQLITE_SELECT_FAILED;
        }
        iCurrentState = oStatement.getColumn(0).getUInt();
    } while (false);

    // 下一步状态
    auto iNextState = ChunkFSM::Transit(iCurrentState, ChunkFSM::FINISH_UPLOAD);
    if (iNextState == ChunkFSM::NOTKNOWN)
    {
        // 状态转移出错，也即当前状态非WRITING
        spdlog::error("FinishUploadSliceHandler current state not match, current: {}, should be: {}", iCurrentState, static_cast<uint32_t>(ChunkFSM::STANDBY));
        return E_CHUNKFSM_TRANSITION_ERROR;
    }

    // RPC 更新远端
    do
    {
        ::chunkserver::SetChunkStateReq oReq;
        ::chunkserver::SetChunkStateRsp oRsp;
        oReq.set_chunk_id(oChunkId.UInt());
        oReq.set_state_to_set(iNextState);
        ChunkServerServiceClient oClient;
        int iRpcRet = oClient.SetChunkState(oReq, oRsp);
        if (iRpcRet != 0)
        {
            spdlog::error("FinishUploadSliceHandler - ChunkServerService.SetChunkState failed, retcode: {}", iRpcRet);
            return E_CHUNKSERVER_SET_CHUNK_STATE_RPC_FAILED;
        }
    } while (false);
    
    // SQLite 更新本地
    do
    {
        int iAffectedRows;
        auto sSql = fmt::format("UPDATE chunks SET state={} WHERE chunk_id={};", iNextState, oChunkId.UInt());
        spdlog::trace(sSql);
        try
        {
            iAffectedRows = g_pSqliteDatabase->exec(sSql);
        }
        catch(const SQLite::Exception& e)
        {
            spdlog::error("FinishUploadSliceHandler UPDATE FAILED: SQL={}, ERRMSG={}", sSql, e.getErrorStr());
            return E_SQLITE_UPDATE_FAILED;
        }
        if (iAffectedRows != 1)
        {
            spdlog::error("FinishUploadSliceHandler UPDATE FAILED: SQL={}", sSql);
            return E_SQLITE_UPDATE_FAILED;
        }
    } while (false);

    return iRet;
}
