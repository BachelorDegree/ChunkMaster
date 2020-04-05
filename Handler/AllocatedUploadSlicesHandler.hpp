#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class AllocatedUploadSlicesHandler final : public AsyncRpcHandler
{
public:
    AllocatedUploadSlicesHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::AllocateUploadSlicesReq                                    request;
    ::chunkmaster::AllocateUploadSlicesRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::AllocateUploadSlicesRsp>  responder;
};
