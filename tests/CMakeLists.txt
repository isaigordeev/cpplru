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
        lru/node_test.cpp lru/lru_test.cpp lru/hash_test.cpp lru/chain_test.cpp
        storage/record_test.cpp
        storage/page_test.cpp)


target_compile_options(cpplru_tests PRIVATE -fsanitize=address -g)
target_link_options(cpplru_tests PRIVATE -fsanitize=address)
target_link_libraries(cpplru_tests PUBLIC
        GTest::gtest_main lru
)

include(GoogleTest)