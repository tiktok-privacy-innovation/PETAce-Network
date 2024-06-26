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

#include "example.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    std::string help_message =
            "For socket:\n"
            "  ./build/bin/network_example socket 127.0.0.1 8899 127.0.0.1 8890\n"
            "  ./build/bin/network_example socket 127.0.0.1 8890 127.0.0.1 8899\n"
            "For agent:\n"
            "  ./build/bin/network_example agent topic ip_a party_a ip_b party_b";

    if (argc < 2) {
        std::cout << help_message << std::endl;
        throw std::runtime_error("Parameters are incorrect!");
    }

    if (std::string(argv[1]) == "socket") {
        if (argc != 6) {
            std::cout << help_message << std::endl;
            throw std::runtime_error("Parameters are incorrect!");
        }
        socket_example(std::string(argv[4]), static_cast<std::uint16_t>(atoi(argv[5])),
                static_cast<std::uint16_t>(atoi(argv[3])));
    } else if (std::string(argv[1]) == "agent") {
#ifdef NETWORK_BUILD_AGENT
        if (argc != 7) {
            std::cout << help_message << std::endl;
            throw std::runtime_error("Parameters are incorrect!");
        }
        agent_example(std::string(argv[2]), std::string(argv[3]), std::string(argv[4]), std::string(argv[5]),
                std::string(argv[6]));
#else
        throw std::runtime_error("NETWORK_BUILD_AGENT is OFF, don't support agent.");
#endif
    } else {
        std::string error_message = "Unknown network scheme: " + std::string(argv[1]);
        throw std::runtime_error(error_message);
    }
    return 0;
}
