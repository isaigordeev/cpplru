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
        lru/node_test.cpp lru/lru_test.cpp lru/hash_test.cpp lru/chain_test.cpp)


target_link_libraries(cpplru_tests PUBLIC
        GTest::gtest_main lru
)
include(GoogleTest)