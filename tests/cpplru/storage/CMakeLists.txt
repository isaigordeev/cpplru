file(GLOB STORAGE_TEST_SOURCES "*.cpp")
add_library(tests_storage OBJECT ${STORAGE_TEST_SOURCES})
target_include_directories(tests_storage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
