cmake_minimum_required(VERSION 3.24)
project(cpplru LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get macOS SDK path dynamically
execute_process(
        COMMAND xcrun --sdk macosx --show-sdk-path
        OUTPUT_VARIABLE MACOS_SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_OSX_SYSROOT ${MACOS_SDK_PATH})

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/clru)

set(SOURCES_C
        clru/lru.c
        clru/hash.c
        clru/chain.c
        clru/node.c
        )

set(SOURCES_CPP
        tests/main.cpp
        )

add_executable(cpplru ${SOURCES_CPP} ${SOURCES_C})

target_compile_options(cpplru PRIVATE -fsanitize=address -g)
target_link_options(cpplru PRIVATE -fsanitize=address)
