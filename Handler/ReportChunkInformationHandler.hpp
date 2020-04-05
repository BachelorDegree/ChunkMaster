#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class ReportChunkInformationHandler final : public AsyncRpcHandler
{
public:
    ReportChunkInformationHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::ReportChunkInformationReq                                    request;
    ::chunkmaster::ReportChunkInformationRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::ReportChunkInformationRsp>  responder;
};
