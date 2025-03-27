add_executable(client main.cpp base_client.cpp ChatClient.cpp)


# Ensure it finds the padawan library
target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/padawan_dll)

# Link against the padawan library
target_link_libraries(client padawan ws2_32)
target_link_directories(client PRIVATE ${CMAKE_BINARY_DIR}/lib)

# Set necessary flags
if (WIN32)
    target_link_options(client PRIVATE -fset-stack-executable)
endif()