#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <coredeps/SatelliteClient.hpp>
#include <coredeps/ContextHelper.hpp>
#include "ChunkServerServiceClient.hpp"
ChunkServerServiceClient::ChunkServerServiceClient()
{
  m_pChannel = GetChannel();
}
ChunkServerServiceClient::ChunkServerServiceClient(const std::string &strIpPortOrCanonicalName)
{
  if (strIpPortOrCanonicalName.find(':') == std::string::npos)
  {
    m_strServiceName = strIpPortOrCanonicalName;
    m_pChannel = this->GetChannel();
  }
  else
  {
    m_pChannel = grpc::CreateChannel(strIpPortOrCanonicalName, grpc::InsecureChannelCredentials());
  }
}
std::shared_ptr<grpc::Channel> ChunkServerServiceClient::GetChannel()
{
  std::string strServer = SatelliteClient::GetInstance().GetNode(m_strServiceName);
  return grpc::CreateChannel(strServer, grpc::InsecureChannelCredentials());
}
int ChunkServerServiceClient::SetChunkStatus(const ::chunkserver::SetChunkStatusReq & oReq, ::chunkserver::SetChunkStatusRsp & oResp)
{
  ::chunkserver::ChunkServerService::Stub oStub{m_pChannel};
  grpc::ClientContext oContext;
  auto oStatus = oStub.SetChunkStatus(&oContext, oReq, &oResp);
  if (oStatus.ok() == false)
  {
    return -1;
  }
  return ClientContextHelper(oContext).GetReturnCode();
}
int ChunkServerServiceClient::AllocateInode(const ::chunkserver::AllocateInodeReq & oReq, ::chunkserver::AllocateInodeRsp & oResp)
{
  ::chunkserver::ChunkServerService::Stub oStub{m_pChannel};
  grpc::ClientContext oContext;
  auto oStatus = oStub.AllocateInode(&oContext, oReq, &oResp);
  if (oStatus.ok() == false)
  {
    return -1;
  }
  return ClientContextHelper(oContext).GetReturnCode();
}
int ChunkServerServiceClient::ReadSlice(const ::chunkserver::ReadSliceReq & oReq, ::chunkserver::ReadSliceRsp & oResp)
{
  ::chunkserver::ChunkServerService::Stub oStub{m_pChannel};
  grpc::ClientContext oContext;
  auto oStatus = oStub.ReadSlice(&oContext, oReq, &oResp);
  if (oStatus.ok() == false)
  {
    return -1;
  }
  return ClientContextHelper(oContext).GetReturnCode();
}
int ChunkServerServiceClient::WriteSlice(const ::chunkserver::WriteSliceReq & oReq, ::chunkserver::WriteSliceRsp & oResp)
{
  ::chunkserver::ChunkServerService::Stub oStub{m_pChannel};
  grpc::ClientContext oContext;
  auto oStatus = oStub.WriteSlice(&oContext, oReq, &oResp);
  if (oStatus.ok() == false)
  {
    return -1;
  }
  return ClientContextHelper(oContext).GetReturnCode();
}
