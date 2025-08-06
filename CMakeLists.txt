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

# Enable testing option
option(BUILD_TESTING "Build tests" ON)

if (BUILD_TESTING)
    enable_testing()
endif ()

# ===============================
# C version library and testing
# ===============================
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
target_include_directories(clru_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/clru)
target_compile_options(clru_test PRIVATE -fsanitize=address -g)
target_link_options(clru_test PRIVATE -fsanitize=address)

# ===============================
# Add C++ libraries
# ===============================
add_subdirectory(cpplru/lru)
add_subdirectory(cpplru/storage)
add_subdirectory(cpplru/auth)
add_subdirectory(cpplru/conc)

# ===============================
# Main executable for C++
# ===============================
add_executable(main
        cpplru/main.cpp
        ${LRU_SOURCES}
        ${AUTH_SOURCES}
        ${STORAGE_SOURCES}
        ${CONC_SOURCES}
)

target_include_directories(main PRIVATE
        ${CMAKE_SOURCE_DIR}/cpplru/lru
        ${CMAKE_SOURCE_DIR}/cpplru/auth
        ${CMAKE_SOURCE_DIR}/cpplru/storage
        ${CMAKE_SOURCE_DIR}/cpplru/conc
)

target_compile_options(main PRIVATE -fsanitize=address -g)
target_link_options(main PRIVATE -fsanitize=address)
target_link_libraries(main PRIVATE lru auth storage conc)

# ===============================
# Tests for C++ libraries
# ===============================


if (BUILD_TESTING)
    add_subdirectory(tests)

    target_include_directories(cpplru_tests PRIVATE ${CMAKE_SOURCE_DIR}/cpplru)
    # Assuming cpplru_tests is defined in tests/CMakeLists.txt
endif ()