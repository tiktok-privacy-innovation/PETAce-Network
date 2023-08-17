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

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "network/net_socket.h"
#include "network/network.h"

namespace petace {
namespace network {

enum class NetScheme : std::uint32_t { SOCKET = 0, GRPC = 1 };

using NetCreator = std::function<std::shared_ptr<Network>(const NetParams& params)>;

/**
 * @brief Network factory.
 *
 * @see Refer to README.md for more details.
 *
 * @par Example.
 * Refer to example.cpp.
 */
class NetFactory {
public:
    /**
     * @brief Get a factory singleton.
     *
     * @return Return factory instance.
     */
    static NetFactory& get_instance() {
        static NetFactory factory;
        return factory;
    }

    /**
     * @brief Get network object based on net scheme.
     *
     * @param[in] scheme: Name of the net
     * @param[in] params: Parameters of the net
     */
    std::shared_ptr<Network> build(const NetScheme& scheme, const NetParams& params) {
        auto where = creator_map_.find(scheme);
        if (where == creator_map_.end()) {
            throw std::invalid_argument("net creator is not registered.");
        }
        return where->second(params);
    }

    /**
     * @brief Register net network
     *
     * @param[in] scheme: Name of the net
     * @param[in] creator: Object of the net
     */
    void register_net(const NetScheme& scheme, NetCreator creator) {
        creator_map_.insert(std::make_pair(scheme, creator));
    }

protected:
    NetFactory() {
        register_net(NetScheme::SOCKET, create_socket);
    }
    ~NetFactory() {
    }
    NetFactory(const NetFactory&) = delete;
    NetFactory& operator=(const NetFactory&) = delete;
    NetFactory(NetFactory&&) = delete;
    NetFactory& operator=(NetFactory&&) = delete;

private:
    std::map<NetScheme, NetCreator> creator_map_;
};

}  // namespace network
}  // namespace petace
