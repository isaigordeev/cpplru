include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Add the test executable
add_executable(cpplru_tests
        # Add source files needed for tests
        ${CMAKE_SOURCE_DIR}/cpplru/lru/node.cpp
        lru/node_test.cpp lru/lru_test.cpp lru/hash_test.cpp lru/chain.cpp)

target_include_directories(cpplru_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/cpplru
        )

target_link_libraries(cpplru_tests
        GTest::gtest_main
        )
include(GoogleTest)