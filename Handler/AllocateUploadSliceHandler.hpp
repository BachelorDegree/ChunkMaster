#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class AllocateUploadSliceHandler final : public AsyncRpcHandler
{
public:
    AllocateUploadSliceHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;
    int  Implementation(void);

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::AllocateUploadSliceReq                                    request;
    ::chunkmaster::AllocateUploadSliceRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::AllocateUploadSliceRsp>  responder;
};
