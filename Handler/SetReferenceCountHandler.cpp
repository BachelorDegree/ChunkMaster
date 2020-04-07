#include <spdlog/spdlog.h>
#include "coredeps/SliceId.hpp"

#include "errcode.h"
#include "Logic/Global.hpp"
#include "Logic/SliceIndexKVHelper.hpp"
#include "ChunkServerServiceClient/ChunkServerServiceClient.hpp"

#include "SetReferenceCountHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

void SetReferenceCountHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.SetReferenceCount";
}

void SetReferenceCountHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestSetReferenceCount(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new SetReferenceCountHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        int iRet = ChunkMasterServiceImpl::GetInstance()->SetReferenceCount(request, response);
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

int SetReferenceCountHandler::Implementation(void)
{
    int iRet = 0;

    std::vector<uint64_t> vecPhysical;
    int iKvRet = SliceIndexKVHelper::GetMapping(request.logical_slice_id(), vecPhysical);
    if (iKvRet != 0)
    {
        spdlog::error("SetReferenceCount - KV get mapping failed, lsid: {}, errcode: {}", 
            request.logical_slice_id(), iKvRet);
        return E_PAXOSKV_GET_RPC_FAILED;
    }

    ::chunkserver::ManipulateReferenceCountReq::OperationType enumOperation;
    switch (request.operation())
    {
    case ::chunkmaster::SetReferenceCountReq::INCREASE:
        enumOperation = ::chunkserver::ManipulateReferenceCountReq::INCREASE;
        break;
    case ::chunkmaster::SetReferenceCountReq::DECREASE:
        enumOperation = ::chunkserver::ManipulateReferenceCountReq::DECREASE;
        break;
    default:
        spdlog::error("SetReferenceCount - operation unknown, lsid: 0x{:016x}", request.logical_slice_id());
        return E_SET_REFCOUNT_OP_UNKNOWN;
    }

    do
    {
        for (const auto iPhysical : vecPhysical)
        {
            Storage::SliceId oPsid(iPhysical);
            auto sCanonical = CanonicalChunkServerName(iPhysical);
            ChunkServerServiceClient oClient(sCanonical);
            ::chunkserver::ManipulateReferenceCountReq oReq;
            ::chunkserver::ManipulateReferenceCountRsp oRsp;
            oReq.set_slice_id(iPhysical);
            oReq.set_operation(enumOperation);
            int iRpcRet = oClient.ManipulateReferenceCount(oReq, oRsp);
            if (iRpcRet != 0)
            {
                spdlog::error("SetReferenceCount - {}.ManipulateReferenceCount failed, req_pb: {}", 
                    sCanonical, oReq.ShortDebugString());
                iRet = E_CHUNKSERVER_MANIP_REFCOUNT_RPC_FAILED;
            }
        }
    } while (false);

    return iRet;
}