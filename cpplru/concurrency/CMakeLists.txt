add_library(conc INTERFACE)

target_link_libraries(conc INTERFACE lru)
target_include_directories(conc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
