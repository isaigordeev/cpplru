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

# === Executable for testing C version ===
set(SOURCES_C
        clru/lru.c
        clru/hash.c
        clru/chain.c
        clru/node.c
        )

set(TEST_C_CPP
        tests/c_main.cpp  # C++ test that uses C implementation
        )

add_executable(clru_test ${TEST_C_CPP} ${SOURCES_C})
target_compile_options(clru_test PRIVATE -fsanitize=address -g)
target_link_options(clru_test PRIVATE -fsanitize=address)


# === Executable for testing C++ version ===
set(CPP_LRU
        lru/lru.cpp     # Your C++ implementation of LRU
        )

set(TEST_CPP
        tests/cpp_main.cpp # Your C++ test for the C++ LRU
        )

add_executable(cpplru_test ${CPP_LRU} ${TEST_CPP})
target_compile_options(cpplru_test PRIVATE -fsanitize=address -g)
target_link_options(cpplru_test PRIVATE -fsanitize=address)
