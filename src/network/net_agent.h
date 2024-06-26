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

#pragma once

#include <memory>
#include <string>

#include "network/grpc_client.h"
#include "network/network.h"

namespace petace {
namespace network {

/**
 * @brief Network which use agent to implement.
 *
 * @see Refer to README.md for more details.
 *
 * @par Example.
 * Refer to example.cpp.
 */
class NetAgent : public Network {
public:
    NetAgent() = delete;

    NetAgent(const NetAgent&) = delete;

    NetAgent& operator=(const NetAgent&) = delete;

    NetAgent(const std::string& shared_topic, const std::string& local_agent, const std::string& remote_party,
            int time_out = 90, bool quiet = true);

    ~NetAgent() = default;

private:
    void send_data_impl(const void* data, std::size_t nbyte) override;

    void recv_data_impl(void* data, std::size_t nbyte) override;

    std::string generate_message_id(uint32_t counter) const;

    void send_grpc_request(const std::string& message_id, const std::string& payload);

    std::string recv_grpc_request(const std::string& message_id);

    bool is_timeout(const std::chrono::high_resolution_clock::time_point& start, int timeout_seconds) const;

    PETNetRpcClient grpc_client_;

    const std::string shared_topic_;
    const std::string remote_party_;
    const std::string local_agent_;

    const int time_out_;
    const bool quiet_;
    std::uint32_t s_counter_ = 0;
    std::uint32_t r_counter_ = 0;
};

inline std::shared_ptr<Network> create_agent(const NetParams& params) {
    return std::make_shared<petace::network::NetAgent>(params.shared_topic, params.local_agent, params.remote_party);
}

}  // namespace network
}  // namespace petace
