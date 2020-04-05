#include "AllocateUploadSlicesHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"
void AllocateUploadSlicesHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.AllocateUploadSlices";
}

void AllocateUploadSlicesHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestAllocateUploadSlices(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new AllocateUploadSlicesHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        // int iRet = ChunkMasterServiceImpl::GetInstance()->AllocateUploadSlices(request, response);
        int iRet = this->Implementation();
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

int AllocateUploadSlicesHandler::Implementation(void)
{
    int iRet = 0;

    return iRet;
}