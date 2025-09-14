cmake_minimum_required(VERSION 3.14)

include(FetchContent)
enable_testing()

# ----------------------------
# Fetch GoogleTest
# ----------------------------
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ----------------------------
# Build C library as static library
# ----------------------------
file(GLOB CLRU_SOURCES "${CMAKE_SOURCE_DIR}/lib/clru/*.c")

add_library(clru STATIC ${CLRU_SOURCES})
target_include_directories(clru PUBLIC "${CMAKE_SOURCE_DIR}/lib/clru")


# ----------------------------
# Function: create object library for each test subdir
# ----------------------------
function(add_test_module SUBDIR)
    file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/*_test.cpp")
    if(TEST_SOURCES)
        string(REPLACE "/" "_" TARGET_NAME "${SUBDIR}")
        add_library(${TARGET_NAME} OBJECT ${TEST_SOURCES})

        # Include project headers, C library headers, and GTest
        target_include_directories(${TARGET_NAME} PRIVATE
            "${CMAKE_SOURCE_DIR}/cpplru"
            ${gtest_SOURCE_DIR}/googletest/include
        )

        # Link GTest so headers propagate
        target_link_libraries(${TARGET_NAME} PUBLIC GTest::gtest)

        set(MODULE_TARGETS "${MODULE_TARGETS};${TARGET_NAME}" PARENT_SCOPE)
    endif()
endfunction()

# ----------------------------
# Automatically scan all immediate subdirectories of tests/
# ----------------------------
file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(DIR ${SUBDIRS})
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}" AND NOT DIR STREQUAL "lib")
        add_test_module(${DIR})
    endif()
endforeach()


# ----------------------------
# Combine all object libraries into a single executable
# ----------------------------
add_executable(cpplru_tests)
foreach(MODULE ${MODULE_TARGETS})
    target_sources(cpplru_tests PRIVATE $<TARGET_OBJECTS:${MODULE}>)
endforeach()

# Link C++ libraries + GTest
target_link_libraries(cpplru_tests PRIVATE
    lru auth storage conc  # C++ libraries from top-level
    GTest::gtest_main
)

# Optional: AddressSanitizer
target_compile_options(cpplru_tests PRIVATE -fsanitize=address -g)
target_link_options(cpplru_tests PRIVATE -fsanitize=address)

# Enable GoogleTest discovery
include(GoogleTest)
gtest_discover_tests(cpplru_tests)
