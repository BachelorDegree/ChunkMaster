#include "ReportChunkInformationHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"
void ReportChunkInformationHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.ReportChunkInformation";
}

void ReportChunkInformationHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestReportChunkInformation(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new ReportChunkInformationHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        int iRet = ChunkMasterServiceImpl::GetInstance()->ReportChunkInformation(request, response);
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

