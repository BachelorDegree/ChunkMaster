#include <spdlog/spdlog.h>
#include "coredeps/SliceId.hpp"

#include "ReportChunkInformationHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

#include "errcode.h"
#include "Logic/SQLite.hpp"

void ReportChunkInformationHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.ReportChunkInformation";
}

void ReportChunkInformationHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestReportChunkInformation(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new ReportChunkInformationHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
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

int ReportChunkInformationHandler::Implementation(void)
{
    int iRet = 0;
    for (int i = 0; i < request.chunk_info_size(); ++i)
    {
        auto pChunkInformation = request.mutable_chunk_info(i);
        auto iChunkState = static_cast<int>(pChunkInformation->state());
        Storage::SliceId oSliceId(pChunkInformation->chunk_id());
        auto sSql = fmt::format("SELECT logical_used, actual_used, state FROM chunks WHERE chunk_id={};", pChunkInformation->chunk_id());
        spdlog::trace(sSql);
        SQLite::Statement oStatement(*g_pSqliteDatabase, sSql);
        bool bIsExecSuccess;
        try
        {
            bIsExecSuccess = oStatement.executeStep();
        }
        catch(const SQLite::Exception& e)
        {
            spdlog::error("ReportChunkInformationHandler SELECT FAILED: SQL={}, ERRMSG={}", sSql, e.getErrorStr());
            return E_SQLITE_SELECT_FAILED;
        }
        if (bIsExecSuccess)
        {
            // 已存在，检查
            auto iStoredLogicalUsed = oStatement.getColumn(0).getUInt(); // logical used
            auto iStoredActualUsed = oStatement.getColumn(1).getUInt(); // actual used
            auto iStoredState = oStatement.getColumn(2).getInt(); // state
            // 判断状态不一致，或master端已用空间小于远端的情况
            if (iStoredLogicalUsed < pChunkInformation->logical_used_space()
                || iStoredActualUsed < pChunkInformation->actual_used_space()
                || iChunkState != iStoredState)
            {
                // 不一致，需要更新
                spdlog::warn("ReportChunkInformationHandler chunk info not match: local: lu={},au={},state={};",
                    iStoredLogicalUsed, iStoredActualUsed, iStoredState);
                spdlog::warn("(cont.) remote: lu={},au={},state={}",
                    pChunkInformation->logical_used_space(), pChunkInformation->actual_used_space(), iChunkState);
                auto sSql = fmt::format(FMT_STRING("UPDATE chunks SET logical_used={}, actual_used={}, state={} WHERE chunk_id={};"), 
                    pChunkInformation->logical_used_space(), pChunkInformation->actual_used_space(), iChunkState, oSliceId.UInt());
                try
                {
                    spdlog::trace(sSql);
                    g_pSqliteDatabase->exec(sSql);
                }
                catch(const SQLite::Exception& e)
                {
                    spdlog::error("ReportChunkInformationHandler UPDATE FAILED: SQL={}, ERRMSG={}", sSql, e.getErrorStr());
                    return E_SQLITE_UPDATE_FAILED;
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            // 不存在，插入
            // auto sSql = fmt::format("INSERT INTO chunks (chunk_id, cluster_id, machine_id, disk_id, logical_used, actual_used, state) VALUES ({}, {}, {}, {}, {}, {}, {});",
            auto sSql = fmt::format("INSERT INTO chunks VALUES ({}, {}, {}, {}, {}, {}, {});",
                oSliceId.UInt(), oSliceId.Cluster(), oSliceId.Machine(), oSliceId.Disk(),
                pChunkInformation->logical_used_space(), pChunkInformation->actual_used_space(), iChunkState);
            try
            {
                spdlog::trace(sSql);
                g_pSqliteDatabase->exec(sSql);
            }
            catch(const SQLite::Exception& e)
            {
                spdlog::error("ReportChunkInformationHandler INSERT FAILED: SQL={}, ERRMSG={}", sSql, e.getErrorStr());
                return E_SQLITE_INSERT_FAILED;
            }
        }
    }
    return iRet;
}
