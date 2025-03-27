add_library(padawan SHARED padawan.cpp)

# Define the export symbol
target_compile_definitions(padawan PRIVATE PADAWAN_EXPORT)

# Link necessary system libraries
target_link_libraries(padawan ws2_32)

# Set linker flags for Windows-specific settings
if (WIN32)
    target_link_options(padawan PRIVATE 
        -Wl,--out-implib=${CMAKE_BINARY_DIR}/lib/padawan.a
        -Wl,--image-base=0x20010000
        -Wl,--disable-dynamicbase
        -fset-stack-executable
    )
endif()