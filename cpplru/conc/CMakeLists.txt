set(CONC_SOURCES
        mutex.cpp
        mutex.h
)

add_library(conc STATIC ${CONC_SOURCES})

target_include_directories(conc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})