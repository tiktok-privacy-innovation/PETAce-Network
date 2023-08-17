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

#include <string>

namespace petace {
namespace network {

struct NetParams {
    std::string local_addr;
    std::uint16_t local_port;
    std::string remote_addr;
    std::uint16_t remote_port;
};

/**
 * @brief PETAce network framework.
 *
 * @see Refer to README.md for more details.
 *
 * @par Example.
 * Refer to example.cpp.
 */
class Network {
public:
    Network() = default;

    virtual ~Network() = default;

    /**
     * @brief Send data from one party to another.
     *
     * @param[in] data Data to be sent, which is byte stream.
     * @param[in] nbyte Byte length of the data.
     */
    void send_data(const void* data, std::size_t nbyte) {
        send_data_impl(data, nbyte);
        bytes_sent_ += nbyte;
    }

    /**
     * @brief Receive data from another party.
     *
     * @param[in] data Data to be received, which is byte stream.
     * @param[in] nbyte Byte length of the data.
     */
    void recv_data(void* data, std::size_t nbyte) {
        recv_data_impl(data, nbyte);
        bytes_received_ += nbyte;
    }

    /**
     * @brief Obtain the amount of data sent over the network.
     *
     * @return Byte length of all the data to be sent.
     */
    std::uint64_t get_bytes_sent() {
        return bytes_sent_;
    }

    /**
     * @brief Obtain the amount of data received over the network.
     *
     * @return Byte length of all the data to be received.
     */
    std::uint64_t get_bytes_received() {
        return bytes_received_;
    }

private:
    virtual void send_data_impl(const void* data, std::size_t nbyte) = 0;

    virtual void recv_data_impl(void* data, std::size_t nbyte) = 0;

    std::uint64_t bytes_sent_ = 0;

    std::uint64_t bytes_received_ = 0;
};

}  // namespace network
}  // namespace petace
