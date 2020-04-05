#include "dylib_export.h"
#include "Proto/chunkmaster.grpc.pb.h"
#include "ChunkMasterServiceImpl.hpp"
#include "Handler/AllocatedUploadSlicesHandler.hpp"
#include "Handler/FinishUploadSliceHandler.hpp"
#include "Handler/ReportChunkInformationHandler.hpp"

::chunkmaster::ChunkMasterService::AsyncService service;

const char * EXPORT_Description(void)
{
    return "chunkmaster";
}

void DoInitialize(const char *);

void EXPORT_DylibInit(const char * conf_file)
{
    ChunkMasterServiceImpl::BeforeServerStart(conf_file);
    DoInitialize(conf_file);
}

grpc::Service * EXPORT_GetGrpcServiceInstance(void)
{
    return &service;
}
void EXPORT_OnCoroutineWorkerStart(void)
{
    ChunkMasterServiceImpl::SetInstance(new ChunkMasterServiceImpl);
    ChunkMasterServiceImpl::GetInstance()->BeforeWorkerStart();
} 
void EXPORT_OnWorkerThreadStart(grpc::ServerCompletionQueue *cq)
{
  // Bind handlers

    new AllocatedUploadSlicesHandler(&service, cq);
    new FinishUploadSliceHandler(&service, cq);
    new ReportChunkInformationHandler(&service, cq);
}
