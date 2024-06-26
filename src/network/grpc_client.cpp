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
// limitations under the License.#include <grpcpp/grpcpp.h>

#include "network/grpc_client.h"

#include <iostream>
#include <stdexcept>

namespace petace {
namespace network {

PETNetRpcClient::PETNetRpcClient(const std::string& server_address, int max_retry, int initial_backoff,
        const std::string& cert_chain, const std::string& private_key, const std::string& root_certs)
        : max_retry_(max_retry), initial_backoff_(initial_backoff) {
    if (!cert_chain.empty() && !private_key.empty() && !root_certs.empty()) {
        grpc::SslCredentialsOptions ssl_opts;
        ssl_opts.pem_cert_chain = cert_chain;
        ssl_opts.pem_private_key = private_key;
        ssl_opts.pem_root_certs = root_certs;
        stub_ = petnet::simple::v1::SimpleRequestServer::NewStub(
                grpc::CreateChannel(server_address, grpc::SslCredentials(ssl_opts)));
        std::cout << "Setup secure channel with " << server_address << std::endl;
    } else {
        stub_ = petnet::simple::v1::SimpleRequestServer::NewStub(
                grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));
        std::cout << "Setup insecure channel with " << server_address << std::endl;
    }
}

bool PETNetRpcClient::ClientSimpleSend(const std::string& message_id, const std::string& receiver_id,
        const std::string& payload, petnet::simple::v1::Response* response) {
    petnet::simple::v1::ClientSimpleSendRequest request;
    request.set_message_id(message_id);
    request.set_receiver_id(receiver_id);
    request.set_payload(payload);

    return Retry(
            [&](grpc::ClientContext* context, const petnet::simple::v1::ClientSimpleSendRequest& send_request,
                    petnet::simple::v1::Response* send_response) {
                return stub_->ClientSimpleSend(context, send_request, send_response);
            },
            request, response);
}

bool PETNetRpcClient::ClientSimpleRecv(const std::string& message_id, petnet::simple::v1::Response* response) {
    petnet::simple::v1::ClientSimpleRecvRequest request;
    request.set_message_id(message_id);

    return Retry(
            [&](grpc::ClientContext* context, const petnet::simple::v1::ClientSimpleRecvRequest& recv_request,
                    petnet::simple::v1::Response* recv_response) {
                return stub_->ClientSimpleRecv(context, recv_request, recv_response);
            },
            request, response);
}

template <typename Req, typename Func>
bool PETNetRpcClient::Retry(const Func& rpc, const Req& request, petnet::simple::v1::Response* response) {
    int backoff = initial_backoff_;
    for (int i = 0; i < max_retry_; ++i) {
        grpc::ClientContext context;

        // Set a deadline for the RPC.
        std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() + std::chrono::seconds(30);
        context.set_deadline(deadline);

        grpc::Status status = rpc(&context, request, response);

        if (status.ok()) {
            return true;
        } else if (status.error_code() == grpc::StatusCode::UNAVAILABLE ||
                   status.error_code() == grpc::StatusCode::DEADLINE_EXCEEDED) {
            std::cout << "Attempt " << i + 1 << " failed with code " << status.error_code()
                      << " and message: " << status.error_message() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(backoff));
            backoff *= 2;  // Exponential backoff.
        } else {
            throw std::runtime_error("Non-retriable error occurred: " + status.error_message());
        }
    }
    return false;
}

}  // namespace network
}  // namespace petace
