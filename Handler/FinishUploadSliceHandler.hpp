#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class FinishUploadSliceHandler final : public AsyncRpcHandler
{
public:
    FinishUploadSliceHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::FinishUploadSliceReq                                    request;
    ::chunkmaster::FinishUploadSliceRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::FinishUploadSliceRsp>  responder;
};
