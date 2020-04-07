#pragma once
#include "Proto/chunkmaster.pb.h"
class ChunkMasterServiceImpl
{
public:
    static ChunkMasterServiceImpl *GetInstance();
    static void SetInstance(ChunkMasterServiceImpl *);
    static int BeforeServerStart(const char * czConf) {
        return 0;
    }
    int BeforeWorkerStart() {
        return 0;
    }
    int CalculateUploadSliceLengths(const ::chunkmaster::CalculateUploadSliceLengthsReq & oReq, ::chunkmaster::CalculateUploadSliceLengthsRsp & oResp);
    int AllocateUploadSlice(const ::chunkmaster::AllocateUploadSliceReq & oReq, ::chunkmaster::AllocateUploadSliceRsp & oResp);
    int FinishUploadSlice(const ::chunkmaster::FinishUploadSliceReq & oReq, ::chunkmaster::FinishUploadSliceRsp & oResp);
    int BatchGetPhysicalSlices(const ::chunkmaster::BatchGetPhysicalSlicesReq & oReq, ::chunkmaster::BatchGetPhysicalSlicesRsp & oResp);
    int SetReferenceCount(const ::chunkmaster::SetReferenceCountReq & oReq, ::chunkmaster::SetReferenceCountRsp & oResp);
    int ReportChunkInformation(const ::chunkmaster::ReportChunkInformationReq & oReq, ::chunkmaster::ReportChunkInformationRsp & oResp);
};
