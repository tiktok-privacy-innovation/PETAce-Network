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

#include "network/network.h"

#include <stdlib.h>
#include <unistd.h>

#include <memory>
#include <string>
#include <thread>

#include "gtest/gtest.h"

#include "network/net_factory.h"

namespace petace {
namespace network {

class NetWorkTest : public ::testing::Test {
public:
    void socket_io(bool is_sender) {
        std::shared_ptr<NetSocket> net;
        if (is_sender) {
            net = std::make_shared<NetSocket>("127.0.0.1", 8890, 8891);
        } else {
            net = std::make_shared<NetSocket>("127.0.0.1", 8891, 8890);
        }

        send_msg_.resize(len_);
        recv_msg_.resize(len_);
        for (std::size_t i = 0; i < len_; i++) {
            send_msg_[i] = static_cast<int64_t>(random());
        }

        if (is_sender) {
            net->send_data(reinterpret_cast<void*>(send_msg_.data()), len_ * sizeof(int64_t));
        } else {
            net->recv_data(reinterpret_cast<void*>(recv_msg_.data()), len_ * sizeof(int64_t));
        }
    }

    void socket_factory(bool is_sender) {
        send_msg_.resize(len_);
        recv_msg_.resize(len_);
        for (std::size_t i = 0; i < len_; i++) {
            send_msg_[i] = static_cast<int64_t>(random());
        }

        NetParams params;
        if (is_sender) {
            params.remote_addr = "127.0.0.1";
            params.remote_port = 8890;
            params.local_addr = "127.0.0.1";
            params.local_port = 8891;
        } else {
            params.remote_addr = "127.0.0.1";
            params.remote_port = 8891;
            params.local_addr = "127.0.0.1";
            params.local_port = 8890;
        }

        auto net = NetFactory::get_instance().build(NetScheme::SOCKET, params);

        if (is_sender) {
            net->send_data(reinterpret_cast<void*>(send_msg_.data()), len_ * sizeof(int64_t));
        } else {
            net->recv_data(reinterpret_cast<void*>(recv_msg_.data()), len_ * sizeof(int64_t));
        }
    }

    void socket_ipv6(bool is_sender) {
        send_msg_.resize(len_);
        recv_msg_.resize(len_);
        for (std::size_t i = 0; i < len_; i++) {
            send_msg_[i] = static_cast<int64_t>(random());
        }

        NetParams params;
        if (is_sender) {
            params.remote_addr = "::ffff:127.0.0.1";
            params.remote_port = 8890;
            params.local_addr = "::ffff:127.0.0.1";
            params.local_port = 8891;
        } else {
            params.remote_addr = "::ffff:127.0.0.1";
            params.remote_port = 8891;
            params.local_addr = "::ffff:127.0.0.1";
            params.local_port = 8890;
        }

        auto net = NetFactory::get_instance().build(NetScheme::SOCKET, params);

        if (is_sender) {
            net->send_data(reinterpret_cast<void*>(send_msg_.data()), len_ * sizeof(int64_t));
        } else {
            net->recv_data(reinterpret_cast<void*>(recv_msg_.data()), len_ * sizeof(int64_t));
        }
    }

public:
    std::size_t len_ = 6400;
    std::vector<int64_t> send_msg_{};
    std::vector<int64_t> recv_msg_{};
    std::thread t_[2];
};

TEST_F(NetWorkTest, socket_io) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        status = -1;
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        socket_io(true);
        exit(EXIT_SUCCESS);
    } else {
        socket_io(false);
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
        for (std::size_t i = 0; i < len_; i++) {
            EXPECT_EQ(send_msg_[i], recv_msg_[i]);
        }
        return;
    }
}

TEST_F(NetWorkTest, socket_factory) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        status = -1;
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        socket_factory(true);
        exit(EXIT_SUCCESS);
    } else {
        socket_factory(false);
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
        for (std::size_t i = 0; i < len_; i++) {
            EXPECT_EQ(send_msg_[i], recv_msg_[i]);
        }
        return;
    }
}

TEST_F(NetWorkTest, socket_ipv6) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        status = -1;
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        socket_ipv6(true);
        exit(EXIT_SUCCESS);
    } else {
        socket_ipv6(false);
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                status = -1;
                break;
            }
        }
        for (std::size_t i = 0; i < len_; i++) {
            EXPECT_EQ(send_msg_[i], recv_msg_[i]);
        }
        return;
    }
}

}  // namespace network
}  // namespace petace
