cmake_minimum_required(VERSION 3.10)
project(Vulnerable_ChatServer)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ensure padawan_dll is included
set(CMAKE_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/padawan_dll")
include_directories(${CMAKE_INCLUDE_PATH})

# Add subdirectories
add_subdirectory(padawan_dll)
add_subdirectory(client)
add_subdirectory(server)
