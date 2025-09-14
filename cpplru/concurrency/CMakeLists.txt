add_library(concurrency INTERFACE)

target_link_libraries(concurrency INTERFACE lru)
target_include_directories(concurrency INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
