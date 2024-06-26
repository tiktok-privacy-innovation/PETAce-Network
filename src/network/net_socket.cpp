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

#include "network/net_socket.h"

#include <future>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>

namespace petace {
namespace network {

NetSocket::NetSocket(const std::string& remote_address, std::uint16_t remote_port, std::uint16_t local_port) {
    try {
        int domain = get_address_family(remote_address);

        // Using two threads running initServer and initClient in parallel to resolve  two instances dead lock.
        auto server_future = std::async(std::launch::async, [this, domain, local_port]() {
            send_socket_ = init_server(domain, local_port);
            set_nodelay(send_socket_);
        });

        auto client_future = std::async(std::launch::async, [this, domain, remote_address, remote_port]() {
            recv_socket_ = init_client(domain, remote_address, remote_port);
            set_nodelay(recv_socket_);
        });

        server_future.get();
        client_future.get();
    } catch (...) {
        clear();
        throw;
    }
}

void NetSocket::clear() {
    if (send_socket_ >= 0) {
        close(send_socket_);
    }
    if (recv_socket_ >= 0) {
        close(recv_socket_);
    }
}

NetSocket::~NetSocket() {
    clear();
}

void NetSocket::set_nodelay(int socket) {
    const int one = 1;
    setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
}

void NetSocket::send_data_impl(const void* data, std::size_t nbyte) {
    std::size_t sent = 0;
    while (sent < nbyte) {
        auto res = send(send_socket_, reinterpret_cast<const char*>(data) + sent, nbyte - sent, 0);
        if (res > 0) {
            sent += static_cast<std::size_t>(res);
        } else {
            throw std::runtime_error("failed to send data");
        }
    }
}

void NetSocket::recv_data_impl(void* data, std::size_t nbyte) {
    std::size_t received = 0;
    while (received < nbyte) {
        ssize_t res = recv(recv_socket_, reinterpret_cast<char*>(data) + received, nbyte - received, 0);
        if (res > 0) {
            received += static_cast<std::size_t>(res);
        } else {
            throw std::runtime_error("failed to receive data");
        }
    }
}

// static
int NetSocket::get_address_family(const std::string& ip_address) {
    addrinfo hints;
    addrinfo* res;
    memset(&hints, 0, sizeof(hints));
    // Allow both IPv4 and IPv6
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // Get address family
    int ret = getaddrinfo(ip_address.c_str(), nullptr, &hints, &res);
    if (ret != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(ret) << std::endl;
        throw std::invalid_argument("invalid ip address");
    }
    int domain = res->ai_family;
    freeaddrinfo(res);
    return domain;
}

// static
int NetSocket::init_server(int domain, std::uint16_t port) {
    sockaddr_storage serv;
    memset(&serv, 0, sizeof(serv));
    socklen_t socksize;
    if (domain == AF_INET) {
        auto* serv_in = reinterpret_cast<sockaddr_in*>(&serv);
        serv_in->sin_family = AF_INET;
        serv_in->sin_addr.s_addr = htonl(INADDR_ANY);
        serv_in->sin_port = htons(port);
        socksize = sizeof(sockaddr_in);
    } else if (domain == AF_INET6) {
        auto* serv_in6 = reinterpret_cast<sockaddr_in6*>(&serv);
        serv_in6->sin6_family = AF_INET6;
        serv_in6->sin6_addr = in6addr_any;
        serv_in6->sin6_port = htons(port);
        socksize = sizeof(sockaddr_in6);
    } else {
        throw std::invalid_argument("invalid domain");
    }

    int server_socket = -1;
    int reuse = 1;
    bool ready_to_accept = false;
    int counter = 60;  // 60 seconds
    while (!ready_to_accept) {
        if (counter <= 0) {
            break;
        } else {
            counter--;
        }
        server_socket = socket(domain, SOCK_STREAM, 0);
        setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
        if (bind(server_socket, (struct sockaddr*)&serv, socksize) < 0 || listen(server_socket, 1) < 0) {
            close(server_socket);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            ready_to_accept = true;
        }
    }

    if (ready_to_accept) {
        sockaddr_storage dest;
        int send_socket = accept(server_socket, (struct sockaddr*)&dest, &socksize);
        close(server_socket);
        return send_socket;
    } else {
        throw std::runtime_error("failed to bind/listen");
    }
}

// static
int NetSocket::init_client(int domain, const std::string& ip_address, std::uint16_t port) {
    std::cout << "Connecting to: " << ip_address << ":" << port << std::endl;
    sockaddr_storage dest;
    socklen_t addr_len;
    memset(&dest, 0, sizeof(dest));
    if (domain == AF_INET) {
        auto* dest_in = reinterpret_cast<sockaddr_in*>(&dest);
        dest_in->sin_family = AF_INET;
        dest_in->sin_addr.s_addr = inet_addr(ip_address.c_str());
        dest_in->sin_port = htons(port);
        addr_len = sizeof(struct sockaddr_in);
    } else if (domain == AF_INET6) {
        auto* dest_in6 = reinterpret_cast<sockaddr_in6*>(&dest);
        dest_in6->sin6_family = AF_INET6;
        inet_pton(AF_INET6, ip_address.c_str(), &dest_in6->sin6_addr);
        dest_in6->sin6_port = htons(port);
        addr_len = sizeof(struct sockaddr_in6);
    } else {
        throw std::invalid_argument("invalid domain");
    }

    int counter = 60 * 2;  // 120 seconds
    while (true) {
        if (counter <= 0) {
            break;
        } else {
            counter--;
        }
        int client_socket = socket(domain, SOCK_STREAM, 0);
        if (connect(client_socket, (struct sockaddr*)&dest, addr_len) == 0) {
            std::cout << "Connected to IP: " << ip_address << ":" << port << std::endl;
            return client_socket;
        }
        close(client_socket);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    throw std::runtime_error("failed to connect");
}

}  // namespace network
}  // namespace petace
