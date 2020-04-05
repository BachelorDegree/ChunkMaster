#include "AllocatedUploadSlicesHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"
void AllocatedUploadSlicesHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.AllocatedUploadSlices";
}

void AllocatedUploadSlicesHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestAllocatedUploadSlices(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new AllocatedUploadSlicesHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        int iRet = ChunkMasterServiceImpl::GetInstance()->AllocatedUploadSlices(request, response);
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

