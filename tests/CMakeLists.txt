include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE LRU_SOURCES
        ${CMAKE_SOURCE_DIR}/cpplru/lru/*.cpp
        ${CMAKE_SOURCE_DIR}/cpplru/lru/*.h
        ${CMAKE_SOURCE_DIR}/cpplru/lru/*.hpp
        )
add_library(cpplru_lib ${LRU_SOURCES})
# Add the test executable
add_executable(cpplru_tests
        # Add source files needed for tests
        lru/node_test.cpp lru/lru_test.cpp lru/hash_test.cpp lru/chain_test.cpp)

target_include_directories(cpplru_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/cpplru
        )

target_link_libraries(cpplru_tests
        GTest::gtest_main
        )
include(GoogleTest)