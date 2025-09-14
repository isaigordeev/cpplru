set(AUTH_SOURCES
        user.cpp
        user.h
)

add_library(auth STATIC ${AUTH_SOURCES})

# target_link_libraries(auth PUBLIC lru)
target_include_directories(auth PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_SOURCE_DIR})