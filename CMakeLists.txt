cmake_minimum_required(VERSION 3.24)
project(cpplru LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")


# Get macOS SDK path dynamically
execute_process(
        COMMAND xcrun --sdk macosx --show-sdk-path
        OUTPUT_VARIABLE MACOS_SDK_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_OSX_SYSROOT ${MACOS_SDK_PATH})

# Enable testing option
option(BUILD_TESTING "Build tests" ON)

if (BUILD_TESTING)
    enable_testing()
endif ()

# ===============================
# C version library and testing
# ===============================
# set(SOURCES_C
#         lib/clru/lru.c
#         lib/clru/hash.c
#         lib/clru/chain.c
#         lib/clru/node.c
#         )

# set(TEST_C_CPP
#         tests/clru/clru_test.cpp  # C++ test that uses C implementation
#         )

# add_executable(clru_test ${TEST_C_CPP} ${SOURCES_C})
# target_include_directories(clru_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/clru)
# target_compile_options(clru_test PRIVATE -fsanitize=address -g)
# target_link_options(clru_test PRIVATE -fsanitize=address)



add_subdirectory(cpplru)


if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()