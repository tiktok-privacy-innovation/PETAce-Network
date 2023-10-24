# Copyright 2023 TikTok Pte. Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.14)

project(NETWORKExamples VERSION 0.2.0 LANGUAGES CXX)

# If not called from root CMakeLists.txt
if(NOT DEFINED NETWORK_BUILD_EXAMPLE)
    set(NETWORK_BUILD_EXAMPLE ON)

    find_package(PETAce-Network 0.2.0 EXACT REQUIRED)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if(NETWORK_BUILD_EXAMPLE)
    # Add source files to example
    set(NETWORK_EXAMPLE_FILES "")
    # Test files in this directory
    set(NETWORK_EXAMPLE_FILES ${NETWORK_EXAMPLE_FILES}
        ${CMAKE_CURRENT_LIST_DIR}/socket_example.cpp
        ${CMAKE_CURRENT_LIST_DIR}/example.cpp
    )

    add_executable(network_example ${NETWORK_EXAMPLE_FILES})

    if(TARGET PETAce-Network::network)
        target_link_libraries(network_example PRIVATE PETAce-Network::network)
    elseif(TARGET PETAce-Network::network_shared)
        target_link_libraries(network_example PRIVATE PETAce-Network::network_shared)
    else()
        message(FATAL_ERROR "Cannot find target PETAce-Network::network or PETAce-Network::network_shared")
    endif()
endif()
