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
    int AllocatedUploadSlices(const ::chunkmaster::AllocateUploadSlicesReq & oReq, ::chunkmaster::AllocateUploadSlicesRsp & oResp);
    int FinishUploadSlice(const ::chunkmaster::FinishUploadSliceReq & oReq, ::chunkmaster::FinishUploadSliceRsp & oResp);
    int ReportChunkInformation(const ::chunkmaster::ReportChunkInformationReq & oReq, ::chunkmaster::ReportChunkInformationRsp & oResp);
};
