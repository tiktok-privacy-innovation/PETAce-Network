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

#include <stdexcept>

//  parameters: local address, local port, remote address, remote port
// ./build/bin/network_example 127.0.0.1 8899 127.0.0.1 8890
// ./build/bin/network_example 127.0.0.1 8890 127.0.0.1 8899
int main(int argc, char* argv[]) {
    if (argc != 5) {
        throw std::runtime_error("Parameters are incorrect!");
    }

    scoket_example(
            std::string(argv[3]), static_cast<std::uint16_t>(atoi(argv[4])), static_cast<std::uint16_t>(atoi(argv[2])));

    return 0;
}
