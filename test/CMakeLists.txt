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

project(NETWORKTest VERSION 0.1.0 LANGUAGES CXX C)

# If not called from root CMakeLists.txt
if(NOT DEFINED NETWORK_BUILD_TEST)
    set(NETWORK_BUILD_TEST ON)

    find_package(PETAce-Network 0.1.0 EXACT REQUIRED)

    # Must define these variables and include macros
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(NETWORK_THIRDPARTY_DIR ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
    set(THIRDPARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
    include(FetchContent)
    mark_as_advanced(FETCHCONTENT_BASE_DIR)
    mark_as_advanced(FETCHCONTENT_FULLY_DISCONNECTED)
    mark_as_advanced(FETCHCONTENT_UPDATES_DISCONNECTED)
    mark_as_advanced(FETCHCONTENT_QUIET)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../cmake)
    include(NetworkCustomMacros)
else()
    set(THIRDPARTY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../thirdparty)
endif()

if(NOT DEFINED NETWORK_BUILD_DEPS)
    # [option] NETWORK_BUILD_DEPS (default: ON)
    # Download and build missing dependencies, throw error if disabled.
    set(NETWORK_BUILD_DEPS_OPTION_STR "Automatically download and build unmet dependencies")
    option(NETWORK_BUILD_DEPS ${NETWORK_BUILD_DEPS_OPTION_STR} ON)
endif()

# if NETWORK_BUILD_TEST is ON, use GoogleTest
if(NETWORK_BUILD_TEST)
    find_package(GTest 1 CONFIG)
    if(GTest_FOUND)
        message(STATUS "GoogleTest: found")
    else()
        if(NETWORK_BUILD_DEPS)
            message(STATUS "GoogleTest: download ...")
            network_fetch_thirdparty_content(ExternalGTest)
            add_library(GTest::gtest ALIAS gtest)
        else()
            message(FATAL_ERROR "GoogleTest: not found, please download and install manually")
        endif()
    endif()

    # Add source files to test
    set(NETWORK_TEST_FILES
        ${CMAKE_CURRENT_LIST_DIR}/network_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/test_runner.cpp
    )

    # CMAKE_CXX_LINK_EXECUTABLE
    if (LINUX)
        set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lrt")
    else()
        set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
    endif()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NETWORK_ENABLE_GCOV)
        set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -fprofile-arcs -ftest-coverage -lgcov")
    endif()

    add_executable(network_test ${NETWORK_TEST_FILES})

    if(TARGET PETAce-Network::network)
        target_link_libraries(network_test PRIVATE PETAce-Network::network GTest::gtest)
    elseif(TARGET PETAce-Network::network_shared)
        target_link_libraries(network_test PRIVATE PETAce-Network::network_shared GTest::gtest)
    else()
        message(FATAL_ERROR "Cannot find target PETAce-Network::network or PETAce-Network::network_shared")
    endif()

    # In Debug mode, enable AddressSanitizer (and LeakSanitizer) on Unix-like platforms.
    if(NETWORK_DEBUG AND UNIX)
        # On macOS, only AddressSanitizer is enabled.
        # On Linux, LeakSanitizer is enabled by default.
        target_compile_options(network_test PUBLIC -fsanitize=address)
        target_link_options(network_test PUBLIC -fsanitize=address)
        if(NOT APPLE)
            message(STATUS "Sanitizers enabled: address, leak")
        else()
            message(STATUS "Sanitizers enabled: address")
        endif()
    endif()

    add_custom_target(test_report
        COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/network_test --gtest_output="xml:${CMAKE_CURRENT_BINARY_DIR}/../report/network_test.xml"
        DEPENDS network_test)
endif()
