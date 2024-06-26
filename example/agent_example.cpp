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

#include <iostream>
#include <vector>

#include "example.h"

#include "network/net_factory.h"

void agent_example(const std::string& shared_topic, const std::string& local_agent, const std::string& local_party,
        const std::string& remote_agent, const std::string& remote_party) {
    std::cout << shared_topic << " " << local_agent << " " << local_party << remote_party << " " << remote_party
              << std::endl;

    petace::network::NetParams local_params;
    local_params.shared_topic = shared_topic;
    local_params.local_agent = local_agent;
    local_params.remote_party = remote_party;

    petace::network::NetParams remote_params;
    remote_params.shared_topic = shared_topic;
    remote_params.local_agent = remote_agent;
    remote_params.remote_party = local_party;

    auto local_net = petace::network::NetFactory::get_instance().build(petace::network::NetScheme::AGENT, local_params);
    auto remote_net =
            petace::network::NetFactory::get_instance().build(petace::network::NetScheme::AGENT, remote_params);

    std::vector<std::uint8_t> send_msgs{0x01, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef};
    local_net->send_data(reinterpret_cast<void*>(send_msgs.data()), send_msgs.size());
    std::cout << "local send message:" << std::endl;
    for (std::size_t i = 0; i < send_msgs.size(); i++) {
        std::cout << std::hex << static_cast<int>(send_msgs[i]) << " ";
    }
    std::cout << std::endl;

    usleep(1000000);

    std::vector<std::uint8_t> recv_msgs(send_msgs.size(), 0);
    remote_net->recv_data(reinterpret_cast<void*>(recv_msgs.data()), recv_msgs.size());
    std::cout << "remote receive message:" << std::endl;
    for (std::size_t i = 0; i < recv_msgs.size(); i++) {
        std::cout << std::hex << static_cast<int>(recv_msgs[i]) << " ";
    }
    std::cout << std::endl;

    remote_net->send_data(reinterpret_cast<void*>(send_msgs.data()), send_msgs.size());
    std::cout << "remote send message:" << std::endl;
    for (std::size_t i = 0; i < send_msgs.size(); i++) {
        std::cout << std::hex << static_cast<int>(send_msgs[i]) << " ";
    }
    std::cout << std::endl;

    usleep(1000000);

    local_net->recv_data(reinterpret_cast<void*>(recv_msgs.data()), recv_msgs.size());
    std::cout << "local receive message:" << std::endl;
    for (std::size_t i = 0; i < recv_msgs.size(); i++) {
        std::cout << std::hex << static_cast<int>(recv_msgs[i]) << " ";
    }
    std::cout << std::endl;
}
