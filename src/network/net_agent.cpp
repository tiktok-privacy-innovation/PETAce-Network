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

#include "network/net_agent.h"

#include <chrono>
#include <cstring>
#include <iostream>

namespace petace {
namespace network {

NetAgent::NetAgent(const std::string& shared_topic, const std::string& local_agent, const std::string& remote_party,
        int time_out, bool quiet)
        : grpc_client_(local_agent),
          shared_topic_(shared_topic),
          remote_party_(remote_party),
          local_agent_(local_agent),
          time_out_(time_out),
          quiet_(quiet) {
}

void NetAgent::send_data_impl(const void* data, std::size_t nbyte) {
    std::string payload(static_cast<const char*>(data), nbyte);
    std::string message_id = generate_message_id(s_counter_++);
    send_grpc_request(message_id, payload);
}

void NetAgent::recv_data_impl(void* data, std::size_t nbyte) {
    const auto start = std::chrono::high_resolution_clock::now();

    while (true) {
        if (is_timeout(start, time_out_)) {
            throw std::runtime_error(
                    "Timeout after " + std::to_string(time_out_) +
                    " seconds while waiting for data with message_id: " + generate_message_id(r_counter_));
        }
        std::string payload = recv_grpc_request(generate_message_id(r_counter_));
        if (payload.size() >= nbyte) {
            memcpy(data, payload.data(), nbyte);
            if (!quiet_) {
                std::cout << "Received data" << std::endl;
            }
            r_counter_++;  // Increment r_counter_ after successful reception
            break;
        }
    }
}

std::string NetAgent::generate_message_id(uint32_t counter) const {
    return shared_topic_ + ":" + std::to_string(counter);
}

void NetAgent::send_grpc_request(const std::string& message_id, const std::string& payload) {
    petnet::simple::v1::Response send_response;
    if (grpc_client_.ClientSimpleSend(message_id, remote_party_, payload, &send_response) and send_response.success()) {
        if (!quiet_) {
            std::cout << "Sent data" << std::endl;
        }
    } else {
        throw std::runtime_error("Failed to send data with message_id: " + message_id + " to: " + remote_party_ +
                                 ", error: " + send_response.error_msg());
    }
}

std::string NetAgent::recv_grpc_request(const std::string& message_id) {
    petnet::simple::v1::Response recv_response;
    if (grpc_client_.ClientSimpleRecv(message_id, &recv_response) and recv_response.success()) {
        return recv_response.payload();
    } else {
        throw std::runtime_error(
                "Failed to receive data with message_id: " + message_id + ", error: " + recv_response.error_msg());
    }
}

bool NetAgent::is_timeout(const std::chrono::high_resolution_clock::time_point& start, int timeout_seconds) const {
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    return elapsed_seconds >= timeout_seconds;
}

}  // namespace network
}  // namespace petace
