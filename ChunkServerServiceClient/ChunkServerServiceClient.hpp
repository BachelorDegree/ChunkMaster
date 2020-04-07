#pragma once
#include <memory>
#include <string>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include "chunkserver.grpc.pb.h"
#include "chunkserver.pb.h"
class ChunkServerServiceClient
{
private:
  std::shared_ptr<grpc::Channel> m_pChannel;
  std::string m_strServiceName;
public:
  ChunkServerServiceClient();
  // User specified IpPort or CanonicalName
  ChunkServerServiceClient(const std::string &strIpPortOrCanonicalName);
  std::shared_ptr<grpc::Channel> GetChannel();
    int SetChunkState(const ::chunkserver::SetChunkStateReq & oReq, ::chunkserver::SetChunkStateRsp & oResp);
    int AllocateInode(const ::chunkserver::AllocateInodeReq & oReq, ::chunkserver::AllocateInodeRsp & oResp);
    int ReadSlice(const ::chunkserver::ReadSliceReq & oReq, ::chunkserver::ReadSliceRsp & oResp);
    int WriteSlice(const ::chunkserver::WriteSliceReq & oReq, ::chunkserver::WriteSliceRsp & oResp);
    int ManipulateReferenceCount(const ::chunkserver::ManipulateReferenceCountReq & oReq, ::chunkserver::ManipulateReferenceCountRsp & oResp);
};
