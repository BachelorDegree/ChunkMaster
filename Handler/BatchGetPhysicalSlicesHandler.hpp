#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class BatchGetPhysicalSlicesHandler final : public AsyncRpcHandler
{
public:
    BatchGetPhysicalSlicesHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;
    int  Implementation(void);

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::BatchGetPhysicalSlicesReq                                    request;
    ::chunkmaster::BatchGetPhysicalSlicesRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::BatchGetPhysicalSlicesRsp>  responder;
};
