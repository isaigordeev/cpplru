set(CONC_SOURCES
        mutex.h
)

add_library(conc STATIC ${CONC_SOURCES})

target_link_libraries(conc PUBLIC lru)
target_include_directories(conc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})