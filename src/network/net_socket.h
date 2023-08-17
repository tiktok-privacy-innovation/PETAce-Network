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

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <memory>
#include <string>

#include "network/network.h"

namespace petace {
namespace network {

/**
 * @brief Network which use socket to implement.
 *
 * @see Refer to README.md for more details.
 *
 * @par Example.
 * Refer to example.cpp.
 */
class NetSocket : public Network {
public:
    NetSocket() = delete;

    NetSocket(const NetSocket&) = delete;

    NetSocket& operator=(const NetSocket&) = delete;

    // The remote_port and local_port must be swapped and not the same if two instance running on same IP.
    NetSocket(const std::string& remote_address, std::uint16_t remote_port, std::uint16_t local_port);

    ~NetSocket() override;

private:
    static void set_nodelay(int socket);

    static void set_delay(int socket);

    void send_data_impl(const void* data, std::size_t nbyte) override;

    void recv_data_impl(void* data, std::size_t nbyte) override;

    static int get_address_family(const std::string& ip_address);

    static int init_server(int domain, std::uint16_t port);

    static int init_client(int domain, const std::string& ip_address, std::uint16_t port);

    int send_socket_ = -1;

    int recv_socket_ = -1;
};

inline std::shared_ptr<Network> create_socket(const NetParams& params) {
    return std::make_shared<petace::network::NetSocket>(params.remote_addr, params.remote_port, params.local_port);
}

}  // namespace network
}  // namespace petace
