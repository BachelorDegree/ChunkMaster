#include <spdlog/spdlog.h>

#include "Logic/SliceIndexKVHelper.hpp"

#include "BatchGetPhysicalSlicesHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

void BatchGetPhysicalSlicesHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.BatchGetPhysicalSlices";
}

void BatchGetPhysicalSlicesHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestBatchGetPhysicalSlices(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new BatchGetPhysicalSlicesHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        // int iRet = ChunkMasterServiceImpl::GetInstance()->BatchGetPhysicalSlices(request, response);
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

int BatchGetPhysicalSlicesHandler::Implementation(void)
{
    int iRet = 0;
    std::vector<uint64_t> vecPhysicalIds;
    vecPhysicalIds.reserve(4);
    for (auto i = 0; i < request.logical_slice_ids_size(); ++i)
    {
        auto iLogicalId = request.logical_slice_ids(i);
        vecPhysicalIds.clear();
        int iHelperRet = SliceIndexKVHelper::GetMapping(iLogicalId, vecPhysicalIds);
        if (iHelperRet != 0)
        {
            spdlog::error("BatchGetPhysicalSlices - KV helper get error, retcode: {}", iHelperRet);
            return iHelperRet;
        }
        auto pResult = response.add_results();
        for (const auto iPhy : vecPhysicalIds)
        {
            pResult->add_physical_slice_id(iPhy);
        }
    }
    return iRet;
}
