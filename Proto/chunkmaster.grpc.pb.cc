// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: chunkmaster.proto

#include "chunkmaster.pb.h"
#include "chunkmaster.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace chunkmaster {

static const char* ChunkMasterService_method_names[] = {
  "/chunkmaster.ChunkMasterService/AllocateUploadSlices",
  "/chunkmaster.ChunkMasterService/FinishUploadSlice",
  "/chunkmaster.ChunkMasterService/ReportChunkInformation",
};

std::unique_ptr< ChunkMasterService::Stub> ChunkMasterService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ChunkMasterService::Stub> stub(new ChunkMasterService::Stub(channel));
  return stub;
}

ChunkMasterService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_AllocateUploadSlices_(ChunkMasterService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_FinishUploadSlice_(ChunkMasterService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ReportChunkInformation_(ChunkMasterService_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ChunkMasterService::Stub::AllocateUploadSlices(::grpc::ClientContext* context, const ::chunkmaster::AllocateUploadSlicesReq& request, ::chunkmaster::AllocateUploadSlicesRsp* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AllocateUploadSlices_, context, request, response);
}

void ChunkMasterService::Stub::experimental_async::AllocateUploadSlices(::grpc::ClientContext* context, const ::chunkmaster::AllocateUploadSlicesReq* request, ::chunkmaster::AllocateUploadSlicesRsp* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AllocateUploadSlices_, context, request, response, std::move(f));
}

void ChunkMasterService::Stub::experimental_async::AllocateUploadSlices(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::chunkmaster::AllocateUploadSlicesRsp* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_AllocateUploadSlices_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::chunkmaster::AllocateUploadSlicesRsp>* ChunkMasterService::Stub::AsyncAllocateUploadSlicesRaw(::grpc::ClientContext* context, const ::chunkmaster::AllocateUploadSlicesReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::chunkmaster::AllocateUploadSlicesRsp>::Create(channel_.get(), cq, rpcmethod_AllocateUploadSlices_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::chunkmaster::AllocateUploadSlicesRsp>* ChunkMasterService::Stub::PrepareAsyncAllocateUploadSlicesRaw(::grpc::ClientContext* context, const ::chunkmaster::AllocateUploadSlicesReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::chunkmaster::AllocateUploadSlicesRsp>::Create(channel_.get(), cq, rpcmethod_AllocateUploadSlices_, context, request, false);
}

::grpc::Status ChunkMasterService::Stub::FinishUploadSlice(::grpc::ClientContext* context, const ::chunkmaster::FinishUploadSliceReq& request, ::chunkmaster::FinishUploadSliceRsp* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_FinishUploadSlice_, context, request, response);
}

void ChunkMasterService::Stub::experimental_async::FinishUploadSlice(::grpc::ClientContext* context, const ::chunkmaster::FinishUploadSliceReq* request, ::chunkmaster::FinishUploadSliceRsp* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_FinishUploadSlice_, context, request, response, std::move(f));
}

void ChunkMasterService::Stub::experimental_async::FinishUploadSlice(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::chunkmaster::FinishUploadSliceRsp* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_FinishUploadSlice_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::chunkmaster::FinishUploadSliceRsp>* ChunkMasterService::Stub::AsyncFinishUploadSliceRaw(::grpc::ClientContext* context, const ::chunkmaster::FinishUploadSliceReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::chunkmaster::FinishUploadSliceRsp>::Create(channel_.get(), cq, rpcmethod_FinishUploadSlice_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::chunkmaster::FinishUploadSliceRsp>* ChunkMasterService::Stub::PrepareAsyncFinishUploadSliceRaw(::grpc::ClientContext* context, const ::chunkmaster::FinishUploadSliceReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::chunkmaster::FinishUploadSliceRsp>::Create(channel_.get(), cq, rpcmethod_FinishUploadSlice_, context, request, false);
}

::grpc::Status ChunkMasterService::Stub::ReportChunkInformation(::grpc::ClientContext* context, const ::chunkmaster::ReportChunkInformationReq& request, ::chunkmaster::ReportChunkInformationRsp* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ReportChunkInformation_, context, request, response);
}

void ChunkMasterService::Stub::experimental_async::ReportChunkInformation(::grpc::ClientContext* context, const ::chunkmaster::ReportChunkInformationReq* request, ::chunkmaster::ReportChunkInformationRsp* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReportChunkInformation_, context, request, response, std::move(f));
}

void ChunkMasterService::Stub::experimental_async::ReportChunkInformation(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::chunkmaster::ReportChunkInformationRsp* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ReportChunkInformation_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::chunkmaster::ReportChunkInformationRsp>* ChunkMasterService::Stub::AsyncReportChunkInformationRaw(::grpc::ClientContext* context, const ::chunkmaster::ReportChunkInformationReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::chunkmaster::ReportChunkInformationRsp>::Create(channel_.get(), cq, rpcmethod_ReportChunkInformation_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::chunkmaster::ReportChunkInformationRsp>* ChunkMasterService::Stub::PrepareAsyncReportChunkInformationRaw(::grpc::ClientContext* context, const ::chunkmaster::ReportChunkInformationReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::chunkmaster::ReportChunkInformationRsp>::Create(channel_.get(), cq, rpcmethod_ReportChunkInformation_, context, request, false);
}

ChunkMasterService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkMasterService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkMasterService::Service, ::chunkmaster::AllocateUploadSlicesReq, ::chunkmaster::AllocateUploadSlicesRsp>(
          std::mem_fn(&ChunkMasterService::Service::AllocateUploadSlices), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkMasterService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkMasterService::Service, ::chunkmaster::FinishUploadSliceReq, ::chunkmaster::FinishUploadSliceRsp>(
          std::mem_fn(&ChunkMasterService::Service::FinishUploadSlice), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ChunkMasterService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ChunkMasterService::Service, ::chunkmaster::ReportChunkInformationReq, ::chunkmaster::ReportChunkInformationRsp>(
          std::mem_fn(&ChunkMasterService::Service::ReportChunkInformation), this)));
}

ChunkMasterService::Service::~Service() {
}

::grpc::Status ChunkMasterService::Service::AllocateUploadSlices(::grpc::ServerContext* context, const ::chunkmaster::AllocateUploadSlicesReq* request, ::chunkmaster::AllocateUploadSlicesRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkMasterService::Service::FinishUploadSlice(::grpc::ServerContext* context, const ::chunkmaster::FinishUploadSliceReq* request, ::chunkmaster::FinishUploadSliceRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ChunkMasterService::Service::ReportChunkInformation(::grpc::ServerContext* context, const ::chunkmaster::ReportChunkInformationReq* request, ::chunkmaster::ReportChunkInformationRsp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace chunkmaster

