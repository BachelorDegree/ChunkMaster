#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <coredeps/SatelliteClient.hpp>
#include <coredeps/ContextHelper.hpp>
#include "IdAllocatorServiceClient.hpp"
IdAllocatorServiceClient::IdAllocatorServiceClient():
  m_strServiceName("IdAllocatorService")
{
  m_pChannel = GetChannel();
}
IdAllocatorServiceClient::IdAllocatorServiceClient(const std::string &strIpPortOrCanonicalName)
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
std::shared_ptr<grpc::Channel> IdAllocatorServiceClient::GetChannel()
{
  std::string strServer = SatelliteClient::GetInstance().GetNode(m_strServiceName);
  return grpc::CreateChannel(strServer, grpc::InsecureChannelCredentials());
}
int IdAllocatorServiceClient::AllocateId(const ::idallocator::AllocateIdReq & oReq, ::idallocator::AllocateIdResp & oResp)
{
  ::idallocator::IdAllocatorService::Stub oStub{m_pChannel};
  grpc::ClientContext oContext;
  auto oStatus = oStub.AllocateId(&oContext, oReq, &oResp);
  if (oStatus.ok() == false)
  {
    return -1;
  }
  return ClientContextHelper(oContext).GetReturnCode();
}
int IdAllocatorServiceClient::BatchAllocateId(const ::idallocator::BatchAllocateIdReq & oReq, ::idallocator::BatchAllocateIdResp & oResp)
{
  ::idallocator::IdAllocatorService::Stub oStub{m_pChannel};
  grpc::ClientContext oContext;
  auto oStatus = oStub.BatchAllocateId(&oContext, oReq, &oResp);
  if (oStatus.ok() == false)
  {
    return -1;
  }
  return ClientContextHelper(oContext).GetReturnCode();
}
