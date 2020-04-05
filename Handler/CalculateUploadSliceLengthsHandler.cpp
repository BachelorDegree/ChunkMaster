#include <cmath>
#include <vector>
#include <spdlog/spdlog.h>

#include "errcode.h"

#include "CalculateUploadSliceLengthsHandler.hpp"
#include "ChunkMasterServiceImpl.hpp"

void CalculateUploadSliceLengthsHandler::SetInterfaceName(void)
{
    interfaceName = "ChunkMasterService.CalculateUploadSliceLengths";
}

void CalculateSlicesLength(uint64_t iDataLength, std::vector<uint32_t> &outLengths)
{
    /* 分片策略：16 MiB 以下直接按 4K 向上取整对齐
    16 MiB 以上，128 MiB 以下的按 16 MiB 一片
    128 MiB 以上的，按 128 MiB 一片 */
    constexpr uint64_t MiB_16 = 16 * 1024 * 1024;
    constexpr uint64_t MiB_128 = 128 * 1024 * 1024;
    if (iDataLength <= MiB_16)
    {
        outLengths.emplace_back(iDataLength);
        return;
    }
    if (iDataLength >= MiB_128)
    {
        auto iCount128 = iDataLength / MiB_128;
        outLengths.reserve(iCount128 + 1);
        for (decltype(iCount128) i = 0; i < iCount128; ++i)
            outLengths.emplace_back(MiB_128);
        outLengths.emplace_back(iDataLength - MiB_128 * iCount128);
        return;
    }
    // 16 < iDataLength < 128
    auto iCount16 = iDataLength / MiB_16;
    outLengths.reserve(iCount16 + 1);
    for (decltype(iCount16) i = 0; i < iCount16; ++i)
        outLengths.emplace_back(MiB_16);
    outLengths.emplace_back(iDataLength - MiB_16 * iCount16);
}

void CalculateUploadSliceLengthsHandler::Proceed(void)
{
    switch (status)
    {
    case Status::CREATE:
        this->SetStatusProcess();
        service->RequestCalculateUploadSliceLengths(&ctx, &request, &responder, cq, cq, this);
        break;
    case Status::PROCESS:
    {
        // Firstly, spawn a new handler for next incoming RPC call
        new CalculateUploadSliceLengthsHandler(service, cq);
        this->BeforeProcess();
        // Implement your logic here
        // int iRet = ChunkMasterServiceImpl::GetInstance()->CalculateUploadSliceLengths(request, response);
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

int CalculateUploadSliceLengthsHandler::Implementation(void)
{
    int iRet = 0;
    auto iDataLength = request.data_length();

    // 计算各个分片的逻辑长度
    std::vector<uint32_t> vecLengths;
    CalculateSlicesLength(iDataLength, vecLengths);

    for (const auto iSliceLength : vecLengths)
    {
        response.add_lengths(iSliceLength);
    }

    spdlog::trace("CalculateUploadSliceLengths - length: {}, rsp pb: {}", iDataLength, response.ShortDebugString());

    return iRet;
}