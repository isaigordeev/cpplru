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


option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# === Executable for testing C version ===
set(SOURCES_C
        lib/clru/lru.c
        lib/clru/hash.c
        lib/clru/chain.c
        lib/clru/node.c
        )

set(TEST_C_CPP
        tests/tests_c_legacy_main.cpp  # C++ test that uses C implementation
        )

add_executable(clru_test ${TEST_C_CPP} ${SOURCES_C})
target_compile_options(clru_test PRIVATE -fsanitize=address -g)
target_link_options(clru_test PRIVATE -fsanitize=address)


# === Executable for testing C++ version ===
set(CPP_LRU
        cpplru/lru/lru.cpp     # Your C++ implementation of LRU
        cpplru/lru/chain.cpp cpplru/lru/chain.h cpplru/lru/hash.cpp cpplru/lru/hash.h cpplru/lru/node.cpp cpplru/lru/node.h)

set(TEST_CPP
        tests/tests_main.cpp # Your C++ test for the C++ LRU
        )

add_executable(cpplru ${CPP_LRU} ${TEST_CPP})

target_include_directories(cpplru PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/clru
        )

target_compile_options(cpplru PRIVATE -fsanitize=address -g)
target_link_options(cpplru PRIVATE -fsanitize=address)
