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

######################################################
# Project NETWORK includes the following components: #
#   1. NETWORK C++ library                           #
#   2. NETWORK C++ test                              #
#   3. NETWORK C++ example                           #
######################################################

# [OPTION] CMAKE_BUILD_TYPE (DEFAULT: "Release")
# Select from Release, Debug, MiniSizeRel, or RelWithDebInfo.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
        STRINGS "Release" "Debug" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "Build type (CMAKE_BUILD_TYPE): ${CMAKE_BUILD_TYPE}")

project(NETWORK VERSION 0.3.0 LANGUAGES CXX C)

########################
# Global configuration #
########################

# CMake modules
include(CMakeDependentOption)
include(CMakePushCheckState)
include(CheckIncludeFiles)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)

# Custom modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(NetworkCustomMacros)

# In Debug mode, define NETWORK_DEBUG.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(NETWORK_DEBUG ON)
else()
    set(NETWORK_DEBUG OFF)
endif()
message(STATUS "NETWORK debug mode: ${NETWORK_DEBUG}")

# In Debug mode, enable extra compiler flags.
include(EnableDebugFlags)

# Always build position-independent-code
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# [OPTION] NETWORK_USE_CXX17 (default: ON)
# Use C++17, use C++14 otherwise.
set(NETWORK_USE_CXX17_OPTION_STR "Use C++17")
option(NETWORK_USE_CXX17 ${NETWORK_USE_CXX17_OPTION_STR} OFF)
message(STATUS "NETWORK_USE_CXX17: ${NETWORK_USE_CXX17}")
# Enable features from C++17 if available, disable features if set to OFF.
include(EnableCXX17)

# Add default files and directories.
include(GNUInstallDirs)

# Runtime path
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Source Tree
set(NETWORK_INCLUDES_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(NETWORK_CONFIG_IN_FILENAME ${CMAKE_CURRENT_LIST_DIR}/cmake/PETAce-NetworkConfig.cmake.in)
set(NETWORK_CONFIG_H_IN_FILENAME ${NETWORK_INCLUDES_DIR}/network/util/config.h.in)

# Build tree
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(NETWORK_CONFIG_FILENAME ${CMAKE_CURRENT_BINARY_DIR}/cmake/PETAce-NetworkConfig.cmake)
set(NETWORK_TARGETS_FILENAME ${CMAKE_CURRENT_BINARY_DIR}/cmake/PETAce-NetworkTargets.cmake)
set(NETWORK_CONFIG_VERSION_FILENAME ${CMAKE_CURRENT_BINARY_DIR}/cmake/PETAce-NetworkConfigVersion.cmake)
set(NETWORK_CONFIG_H_FILENAME ${CMAKE_CURRENT_BINARY_DIR}/src/network/util/config.h)
set(NETWORK_THIRDPARTY_DIR ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)

# Installation tree
set(NETWORK_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/PETAce-Network-${NETWORK_VERSION_MAJOR}.${NETWORK_VERSION_MINOR})
set(NETWORK_INCLUDES_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/PETAce-${NETWORK_VERSION_MAJOR}.${NETWORK_VERSION_MINOR})
set(NETWORK_THIRDPARTY_INCLUDES_INSTALL_DIR ${NETWORK_INCLUDES_INSTALL_DIR}/thirdparty)

# Make the install target depend on the all target.
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY OFF)

# Supported target operating systems are Linux and macOS.
if (NOT DEFINED LINUX)
    if (UNIX AND NOT APPLE AND NOT CYGWIN AND NOT MINGW)
        set(LINUX ON)
    endif()
endif()
if (UNIX AND APPLE)
    set(MACOS ON)
endif()
if (NOT LINUX AND NOT MACOS)
    message(FATAL_ERROR "Supported target operating systems are Linux and macOS")
endif()

# Only support x86_64 and arm64
set(CMAKE_REQUIRED_QUIET_OLD ${CMAKE_REQUIRED_QUIET})
set(CMAKE_REQUIRED_QUIET ON)
check_cxx_source_runs("
    #if defined(__aarch64__)
        int main() {
            return 0;
        }
    #else
        #error
    #endif
    "
    NETWORK_ARM64
)
check_cxx_source_runs("
    #if defined(__amd64)
        int main() {
            return 0;
        }
    #else
        #error
    #endif
    "
    NETWORK_AMD64
)
set(CMAKE_REQUIRED_QUIET ${CMAKE_REQUIRED_QUIET_OLD})
if (NOT NETWORK_AMD64 AND NOT NETWORK_ARM64)
    message(FATAL_ERROR "Supported target architectures are x86_64 and arm64")
endif()

# Enable test coverage
set(NETWORK_ENABLE_GCOV_STR "Enable gcov")
option(NETWORK_ENABLE_GCOV ${NETWORK_ENABLE_GCOV_STR} OFF)
message(STATUS "NETWORK_ENABLE_GCOV: ${NETWORK_ENABLE_GCOV_STR}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NETWORK_ENABLE_GCOV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    if (LINUX)
        set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -fprofile-arcs -ftest-coverage -lgcov")
    else()
        set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -fprofile-arcs -ftest-coverage")
    endif()
endif()

# CMAKE_CXX_LINK_EXECUTABLE
if (LINUX)
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl -lrt")
else()
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
endif()

#########################
# External dependencies #
#########################

# [OPTION] NETWORK_BUILD_DEPS (DEFAULT: ON)
# Download and build dependencies if set to ON.
# Look for dependencies using find_package, otherwise.
set(NETWORK_BUILD_DEPS_OPTION_STR "Automatically download and build unmet dependencies")
option(NETWORK_BUILD_DEPS ${NETWORK_BUILD_DEPS_OPTION_STR} ON)
message(STATUS "NETWORK_BUILD_DEPS: ${NETWORK_BUILD_DEPS}")

set(NETWORK_BUILD_AGENT_STR "Build Agent")
option(NETWORK_BUILD_AGENT ${NETWORK_BUILD_AGENT_STR} OFF)
message(STATUS "NETWORK_BUILD_AGENT: ${NETWORK_BUILD_AGENT}")

if(NETWORK_BUILD_DEPS)
    include(FetchContent)
    mark_as_advanced(FETCHCONTENT_BASE_DIR)
    mark_as_advanced(FETCHCONTENT_FULLY_DISCONNECTED)
    mark_as_advanced(FETCHCONTENT_UPDATES_DISCONNECTED)
    mark_as_advanced(FETCHCONTENT_QUIET)
endif()

# Require Threads::Threads
if(NOT TARGET Threads::Threads)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
endif()

if(NETWORK_BUILD_AGENT)
    # protobuf::libprotobuf
    if(NOT TARGET protobuf::libprotobuf)
        find_package(protobuf QUIET REQUIRED)
        if(protobuf_FOUND)
            message(STATUS "protobuf: found")
        else()
            message(FATAL_ERROR "protobuf: not found, please download and install manually")
        endif()
    endif()

    # gRPC::grpc++
    if(NOT TARGET gRPC::grpc++)
        find_package(gRPC 1.62 QUIET REQUIRED)
        if(gRPC_FOUND)
            message(STATUS "grpc: found")
        else()
            message(FATAL_ERROR "grpc: not found, please download and install manually")
        endif()
    endif()
endif()

#######################
# NETWORK C++ library #
#######################

# [OPTION] NETWORK_BUILD_SHARED_LIBS (DEFAULT: OFF)
# Build a shared library if set to ON.
set(NETWORK_BUILD_SHARED_LIBS_STR "Build shared library")
option(NETWORK_BUILD_SHARED_LIBS ${NETWORK_BUILD_SHARED_LIBS_STR} OFF)
message(STATUS "NETWORK_BUILD_SHARED_LIBS: ${NETWORK_BUILD_SHARED_LIBS}")

# Add source files to library and header files to install
set(NETWORK_SOURCE_FILES "")
add_subdirectory(src/network)

# Create the config file
configure_file(${NETWORK_CONFIG_H_IN_FILENAME} ${NETWORK_CONFIG_H_FILENAME})
install(
    FILES ${NETWORK_CONFIG_H_FILENAME}
    DESTINATION ${NETWORK_INCLUDES_INSTALL_DIR}/network/util)

# Build only a static library
if(NOT NETWORK_BUILD_SHARED_LIBS)
    add_library(network STATIC ${NETWORK_SOURCE_FILES})
    if(NETWORK_USE_CXX17)
        target_compile_features(network PUBLIC cxx_std_17)
    else()
        target_compile_features(network PUBLIC cxx_std_14)
    endif()
    target_include_directories(network PUBLIC
        $<BUILD_INTERFACE:${NETWORK_INCLUDES_DIR}>
        $<INSTALL_INTERFACE:${NETWORK_INCLUDES_INSTALL_DIR}>)
    target_include_directories(network PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/>)
    set_target_properties(network PROPERTIES VERSION ${NETWORK_VERSION})
    set_target_properties(network PROPERTIES OUTPUT_NAME petace_network-${NETWORK_VERSION_MAJOR}.${NETWORK_VERSION_MINOR})

    if(NETWORK_BUILD_AGENT)
        target_link_libraries(network PUBLIC gRPC::grpc++)
        target_link_libraries(network PUBLIC protobuf::libprotobuf)
    endif()

    install(TARGETS network EXPORT PETAce-NetworkTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    target_link_libraries(network PUBLIC Threads::Threads)

# Build only a shared library
else()
    add_library(network_shared SHARED ${NETWORK_SOURCE_FILES})
    if(NETWORK_USE_CXX17)
        target_compile_features(network_shared PUBLIC cxx_std_17)
    else()
        target_compile_features(network_shared PUBLIC cxx_std_14)
    endif()
    target_include_directories(network_shared PUBLIC
        $<BUILD_INTERFACE:${NETWORK_INCLUDES_DIR}>
        $<INSTALL_INTERFACE:${NETWORK_INCLUDES_INSTALL_DIR}>)
    target_include_directories(network_shared PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/>)
    set_target_properties(network_shared PROPERTIES VERSION ${NETWORK_VERSION})
    set_target_properties(network_shared PROPERTIES SOVERSION ${NETWORK_VERSION_MAJOR}.${NETWORK_VERSION_MINOR})
    set_target_properties(network_shared PROPERTIES OUTPUT_NAME petace_network)

    if(NETWORK_BUILD_AGENT)
        target_link_libraries(network_shared PUBLIC gRPC::grpc++)
        target_link_libraries(network_shared PUBLIC protobuf::libprotobuf)
    endif()

    install(TARGETS network_shared EXPORT PETAce-NetworkTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    target_link_libraries(network_shared PUBLIC Threads::Threads)
endif()

# Add standard alias targets for PETAce-Network::network and PETAce::network_shared
if(TARGET network)
    add_library(PETAce-Network::network ALIAS network)
endif()
if(TARGET network_shared)
    add_library(PETAce-Network::network_shared ALIAS network_shared)
endif()

#################################
# Installation and CMake config #
#################################

# Create the CMake config file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${NETWORK_CONFIG_IN_FILENAME} ${NETWORK_CONFIG_FILENAME}
    INSTALL_DESTINATION ${NETWORK_CONFIG_INSTALL_DIR})

# Install the export
install(
    EXPORT PETAce-NetworkTargets
    NAMESPACE PETAce-Network::
    DESTINATION ${NETWORK_CONFIG_INSTALL_DIR})

# Version file; we require exact version match for downstream
write_basic_package_version_file(
    ${NETWORK_CONFIG_VERSION_FILENAME}
    VERSION ${NETWORK_VERSION}
    COMPATIBILITY SameMinorVersion)

# Install config and module files
install(
    FILES
        ${NETWORK_CONFIG_FILENAME}
        ${NETWORK_CONFIG_VERSION_FILENAME}
    DESTINATION ${NETWORK_CONFIG_INSTALL_DIR})

# We export PETAce-NetworkTargets from the build tree so it can be used by other projects
# without requiring an install.
export(
    EXPORT PETAce-NetworkTargets
    NAMESPACE PETAce-Network::
    FILE ${NETWORK_TARGETS_FILENAME})

# Install header files of dependencies if NETWORK_BUILD_DEPS is ON
if(NETWORK_BUILD_DEPS)
    # Insert dependencies here
endif()

#######################
# NETWORK C++ example #
#######################

# [option] NETWORK_BUILD_EXAMPLE
set(NETWORK_BUILD_EXAMPLE_OPTION_STR "Build C++ example for NETWORK")
option(NETWORK_BUILD_EXAMPLE ${NETWORK_BUILD_EXAMPLE_OPTION_STR} ON)
message(STATUS "NETWORK_BUILD_EXAMPLE: ${NETWORK_BUILD_EXAMPLE}")

if(NETWORK_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

####################
# NETWORK C++ test #
####################

# [option] NETWORK_BUILD_TEST
set(NETWORK_BUILD_TEST_OPTION_STR "Build C++ test for NETWORK")
option(NETWORK_BUILD_TEST ${NETWORK_BUILD_TEST_OPTION_STR} ON)
message(STATUS "NETWORK_BUILD_TEST: ${NETWORK_BUILD_TEST}")

if(NETWORK_BUILD_TEST)
    add_subdirectory(test)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NETWORK_ENABLE_GCOV)
    add_custom_target(test_coverage
        COMMAND gcovr -r ${CMAKE_CURRENT_LIST_DIR} -f \"src\" -e \".+\(test\\.cpp\)\" --xml-pretty -o "${CMAKE_CURRENT_BINARY_DIR}/report/coverage.xml"
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
  endif()
endif()
