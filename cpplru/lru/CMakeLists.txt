set(LRU_SOURCES
        lru.cpp
        chain.cpp
        hash.cpp
        node.cpp
)

add_library(lru STATIC ${LRU_SOURCES})

target_include_directories(lru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})