// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: simple.proto
// Original file comments:
// Copyright 2023 TikTok Pte. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_simple_2eproto__INCLUDED
#define GRPC_simple_2eproto__INCLUDED

#include "simple.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace petnet {
namespace simple {
namespace v1 {

class SimpleRequestServer final {
 public:
  static constexpr char const* service_full_name() {
    return "petnet.simple.v1.SimpleRequestServer";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // client send data to local server
    virtual ::grpc::Status ClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::petnet::simple::v1::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>> AsyncClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>>(AsyncClientSimpleSendRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>> PrepareAsyncClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>>(PrepareAsyncClientSimpleSendRaw(context, request, cq));
    }
    // client recv data from local server
    virtual ::grpc::Status ClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::petnet::simple::v1::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>> AsyncClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>>(AsyncClientSimpleRecvRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>> PrepareAsyncClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>>(PrepareAsyncClientSimpleRecvRaw(context, request, cq));
    }
    // local server send data to remote server
    virtual ::grpc::Status ServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::petnet::simple::v1::Response* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>> AsyncServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>>(AsyncServerSimpleSendRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>> PrepareAsyncServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>>(PrepareAsyncServerSimpleSendRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // client send data to local server
      virtual void ClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest* request, ::petnet::simple::v1::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest* request, ::petnet::simple::v1::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // client recv data from local server
      virtual void ClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::petnet::simple::v1::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::petnet::simple::v1::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // local server send data to remote server
      virtual void ServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest* request, ::petnet::simple::v1::Response* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest* request, ::petnet::simple::v1::Response* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>* AsyncClientSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>* PrepareAsyncClientSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>* AsyncClientSimpleRecvRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>* PrepareAsyncClientSimpleRecvRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>* AsyncServerSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::petnet::simple::v1::Response>* PrepareAsyncServerSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status ClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::petnet::simple::v1::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>> AsyncClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>>(AsyncClientSimpleSendRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>> PrepareAsyncClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>>(PrepareAsyncClientSimpleSendRaw(context, request, cq));
    }
    ::grpc::Status ClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::petnet::simple::v1::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>> AsyncClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>>(AsyncClientSimpleRecvRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>> PrepareAsyncClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>>(PrepareAsyncClientSimpleRecvRaw(context, request, cq));
    }
    ::grpc::Status ServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::petnet::simple::v1::Response* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>> AsyncServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>>(AsyncServerSimpleSendRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>> PrepareAsyncServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>>(PrepareAsyncServerSimpleSendRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void ClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest* request, ::petnet::simple::v1::Response* response, std::function<void(::grpc::Status)>) override;
      void ClientSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest* request, ::petnet::simple::v1::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
      void ClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::petnet::simple::v1::Response* response, std::function<void(::grpc::Status)>) override;
      void ClientSimpleRecv(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::petnet::simple::v1::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
      void ServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest* request, ::petnet::simple::v1::Response* response, std::function<void(::grpc::Status)>) override;
      void ServerSimpleSend(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest* request, ::petnet::simple::v1::Response* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>* AsyncClientSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>* PrepareAsyncClientSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>* AsyncClientSimpleRecvRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>* PrepareAsyncClientSimpleRecvRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>* AsyncServerSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::petnet::simple::v1::Response>* PrepareAsyncServerSimpleSendRaw(::grpc::ClientContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_ClientSimpleSend_;
    const ::grpc::internal::RpcMethod rpcmethod_ClientSimpleRecv_;
    const ::grpc::internal::RpcMethod rpcmethod_ServerSimpleSend_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // client send data to local server
    virtual ::grpc::Status ClientSimpleSend(::grpc::ServerContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest* request, ::petnet::simple::v1::Response* response);
    // client recv data from local server
    virtual ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::petnet::simple::v1::Response* response);
    // local server send data to remote server
    virtual ::grpc::Status ServerSimpleSend(::grpc::ServerContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest* request, ::petnet::simple::v1::Response* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_ClientSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ClientSimpleSend() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_ClientSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestClientSimpleSend(::grpc::ServerContext* context, ::petnet::simple::v1::ClientSimpleSendRequest* request, ::grpc::ServerAsyncResponseWriter< ::petnet::simple::v1::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_ClientSimpleRecv : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ClientSimpleRecv() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_ClientSimpleRecv() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestClientSimpleRecv(::grpc::ServerContext* context, ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::grpc::ServerAsyncResponseWriter< ::petnet::simple::v1::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_ServerSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ServerSimpleSend() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_ServerSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ServerSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestServerSimpleSend(::grpc::ServerContext* context, ::petnet::simple::v1::ServerSimpleSendRequest* request, ::grpc::ServerAsyncResponseWriter< ::petnet::simple::v1::Response>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_ClientSimpleSend<WithAsyncMethod_ClientSimpleRecv<WithAsyncMethod_ServerSimpleSend<Service > > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_ClientSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ClientSimpleSend() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::petnet::simple::v1::ClientSimpleSendRequest, ::petnet::simple::v1::Response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::petnet::simple::v1::ClientSimpleSendRequest* request, ::petnet::simple::v1::Response* response) { return this->ClientSimpleSend(context, request, response); }));}
    void SetMessageAllocatorFor_ClientSimpleSend(
        ::grpc::MessageAllocator< ::petnet::simple::v1::ClientSimpleSendRequest, ::petnet::simple::v1::Response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::petnet::simple::v1::ClientSimpleSendRequest, ::petnet::simple::v1::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_ClientSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ClientSimpleSend(
      ::grpc::CallbackServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_ClientSimpleRecv : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ClientSimpleRecv() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::petnet::simple::v1::ClientSimpleRecvRequest, ::petnet::simple::v1::Response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::petnet::simple::v1::ClientSimpleRecvRequest* request, ::petnet::simple::v1::Response* response) { return this->ClientSimpleRecv(context, request, response); }));}
    void SetMessageAllocatorFor_ClientSimpleRecv(
        ::grpc::MessageAllocator< ::petnet::simple::v1::ClientSimpleRecvRequest, ::petnet::simple::v1::Response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::petnet::simple::v1::ClientSimpleRecvRequest, ::petnet::simple::v1::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_ClientSimpleRecv() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ClientSimpleRecv(
      ::grpc::CallbackServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_ServerSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ServerSimpleSend() {
      ::grpc::Service::MarkMethodCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::petnet::simple::v1::ServerSimpleSendRequest, ::petnet::simple::v1::Response>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::petnet::simple::v1::ServerSimpleSendRequest* request, ::petnet::simple::v1::Response* response) { return this->ServerSimpleSend(context, request, response); }));}
    void SetMessageAllocatorFor_ServerSimpleSend(
        ::grpc::MessageAllocator< ::petnet::simple::v1::ServerSimpleSendRequest, ::petnet::simple::v1::Response>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(2);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::petnet::simple::v1::ServerSimpleSendRequest, ::petnet::simple::v1::Response>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_ServerSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ServerSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ServerSimpleSend(
      ::grpc::CallbackServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_ClientSimpleSend<WithCallbackMethod_ClientSimpleRecv<WithCallbackMethod_ServerSimpleSend<Service > > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_ClientSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ClientSimpleSend() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_ClientSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_ClientSimpleRecv : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ClientSimpleRecv() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_ClientSimpleRecv() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_ServerSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ServerSimpleSend() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_ServerSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ServerSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_ClientSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ClientSimpleSend() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_ClientSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestClientSimpleSend(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_ClientSimpleRecv : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ClientSimpleRecv() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_ClientSimpleRecv() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestClientSimpleRecv(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_ServerSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ServerSimpleSend() {
      ::grpc::Service::MarkMethodRaw(2);
    }
    ~WithRawMethod_ServerSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ServerSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestServerSimpleSend(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ClientSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ClientSimpleSend() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->ClientSimpleSend(context, request, response); }));
    }
    ~WithRawCallbackMethod_ClientSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ClientSimpleSend(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ClientSimpleRecv : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ClientSimpleRecv() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->ClientSimpleRecv(context, request, response); }));
    }
    ~WithRawCallbackMethod_ClientSimpleRecv() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ClientSimpleRecv(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ServerSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ServerSimpleSend() {
      ::grpc::Service::MarkMethodRawCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->ServerSimpleSend(context, request, response); }));
    }
    ~WithRawCallbackMethod_ServerSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ServerSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ServerSimpleSend(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ClientSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_ClientSimpleSend() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::petnet::simple::v1::ClientSimpleSendRequest, ::petnet::simple::v1::Response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::petnet::simple::v1::ClientSimpleSendRequest, ::petnet::simple::v1::Response>* streamer) {
                       return this->StreamedClientSimpleSend(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_ClientSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ClientSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedClientSimpleSend(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::petnet::simple::v1::ClientSimpleSendRequest,::petnet::simple::v1::Response>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ClientSimpleRecv : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_ClientSimpleRecv() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::petnet::simple::v1::ClientSimpleRecvRequest, ::petnet::simple::v1::Response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::petnet::simple::v1::ClientSimpleRecvRequest, ::petnet::simple::v1::Response>* streamer) {
                       return this->StreamedClientSimpleRecv(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_ClientSimpleRecv() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ClientSimpleRecv(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ClientSimpleRecvRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedClientSimpleRecv(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::petnet::simple::v1::ClientSimpleRecvRequest,::petnet::simple::v1::Response>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ServerSimpleSend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_ServerSimpleSend() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler<
          ::petnet::simple::v1::ServerSimpleSendRequest, ::petnet::simple::v1::Response>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::petnet::simple::v1::ServerSimpleSendRequest, ::petnet::simple::v1::Response>* streamer) {
                       return this->StreamedServerSimpleSend(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_ServerSimpleSend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ServerSimpleSend(::grpc::ServerContext* /*context*/, const ::petnet::simple::v1::ServerSimpleSendRequest* /*request*/, ::petnet::simple::v1::Response* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedServerSimpleSend(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::petnet::simple::v1::ServerSimpleSendRequest,::petnet::simple::v1::Response>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_ClientSimpleSend<WithStreamedUnaryMethod_ClientSimpleRecv<WithStreamedUnaryMethod_ServerSimpleSend<Service > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_ClientSimpleSend<WithStreamedUnaryMethod_ClientSimpleRecv<WithStreamedUnaryMethod_ServerSimpleSend<Service > > > StreamedService;
};

}  // namespace v1
}  // namespace simple
}  // namespace petnet


#endif  // GRPC_simple_2eproto__INCLUDED
