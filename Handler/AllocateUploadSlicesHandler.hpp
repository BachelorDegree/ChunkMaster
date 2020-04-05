#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class AllocateUploadSlicesHandler final : public AsyncRpcHandler
{
public:
    AllocateUploadSlicesHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;
    int  Implementation(void);

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::AllocateUploadSlicesReq                                    request;
    ::chunkmaster::AllocateUploadSlicesRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::AllocateUploadSlicesRsp>  responder;
};
