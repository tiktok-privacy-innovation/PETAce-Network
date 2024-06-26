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

#include <grpcpp/grpcpp.h>

#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "network/proto/simple.grpc.pb.h"
#include "network/proto/simple.pb.h"

namespace petace {
namespace network {

/**
 * @brief Provides a RPC client to interact with the PETNet server.
 */
class PETNetRpcClient {
public:
    PETNetRpcClient(const std::string& server_address, int max_retry = 3, int initial_backoff = 1,
            const std::string& cert_chain = "", const std::string& private_key = "",
            const std::string& root_certs = "");

    bool ClientSimpleSend(const std::string& message_id, const std::string& receiver_id, const std::string& payload,
            petnet::simple::v1::Response* response);

    bool ClientSimpleRecv(const std::string& message_id, petnet::simple::v1::Response* response);

private:
    template <typename Req, typename Func>
    bool Retry(const Func& rpc, const Req& request, petnet::simple::v1::Response* response);

    std::unique_ptr<petnet::simple::v1::SimpleRequestServer::Stub> stub_;
    const int max_retry_;
    const int initial_backoff_;
};

}  // namespace network
}  // namespace petace
