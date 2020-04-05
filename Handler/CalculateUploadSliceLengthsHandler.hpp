#pragma once

#include "AsyncRpcHandler.hpp"
#include "Proto/chunkmaster.grpc.pb.h"

class CalculateUploadSliceLengthsHandler final : public AsyncRpcHandler
{
public:
    CalculateUploadSliceLengthsHandler(::chunkmaster::ChunkMasterService::AsyncService *service, grpc::ServerCompletionQueue *cq):
        AsyncRpcHandler(cq), service(service), responder(&ctx)
    {
        this->Proceed();
    }
    void Proceed(void) override;
    void SetInterfaceName(void) override;
    int  Implementation(void);

private:
    ::chunkmaster::ChunkMasterService::AsyncService*                     service;
    ::chunkmaster::CalculateUploadSliceLengthsReq                                    request;
    ::chunkmaster::CalculateUploadSliceLengthsRsp                                   response;
    grpc::ServerAsyncResponseWriter<::chunkmaster::CalculateUploadSliceLengthsRsp>  responder;
};
