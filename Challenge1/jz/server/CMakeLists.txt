add_executable(server main.cpp base_listening_server.cpp ChatServer.cpp MessageQueue.cpp)

# Link against the padawan library
target_link_libraries(server padawan ws2_32)

# Ensure it finds the padawan library
target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/padawan_dll)
target_link_directories(server PRIVATE ${CMAKE_BINARY_DIR}/lib)

# Set necessary flags
if (WIN32)
    target_link_options(server PRIVATE -fset-stack-executable)
endif()