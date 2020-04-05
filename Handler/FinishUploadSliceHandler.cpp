#include "FinishUploadSliceHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"
void FinishUploadSliceHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.FinishUploadSlice";
}

void FinishUploadSliceHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestFinishUploadSlice(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new FinishUploadSliceHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        int iRet = ChunkMasterServiceImpl::GetInstance()->FinishUploadSlice(request, response);
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

