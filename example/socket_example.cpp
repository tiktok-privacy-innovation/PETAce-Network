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

void socket_example(const std::string& remote_address, std::uint16_t remote_port, std::uint16_t local_port) {
    petace::network::NetParams params;
    params.remote_addr = remote_address;
    params.remote_port = remote_port;
    params.local_port = local_port;

    auto net = petace::network::NetFactory::get_instance().build(petace::network::NetScheme::SOCKET, params);

    std::vector<std::uint8_t> send_msgs{0x01, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef};
    std::vector<std::uint8_t> recv_msgs(send_msgs.size(), 0);
    net->send_data(reinterpret_cast<void*>(send_msgs.data()), send_msgs.size());
    net->recv_data(reinterpret_cast<void*>(recv_msgs.data()), recv_msgs.size());

    std::cout << "send message:" << std::endl;
    for (std::size_t i = 0; i < send_msgs.size(); i++) {
        std::cout << std::hex << static_cast<int>(send_msgs[i]) << " ";
    }
    std::cout << std::endl;

    std::cout << "receive message:" << std::endl;
    for (std::size_t i = 0; i < recv_msgs.size(); i++) {
        std::cout << std::hex << static_cast<int>(recv_msgs[i]) << " ";
    }
    std::cout << std::endl;
}
