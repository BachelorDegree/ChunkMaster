#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class SetReferenceCountHandler final : public AsyncRpcHandler
{
public:
    SetReferenceCountHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;
    int  Implementation(void);

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::SetReferenceCountReq                                    request;
    ::chunkmaster::SetReferenceCountRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::SetReferenceCountRsp>  responder;
};
