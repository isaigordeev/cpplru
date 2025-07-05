set(STORAGE_SOURCES
        buffer.cpp
        buffer.h
        record.cpp
        record.h
)

add_library(storage STATIC ${STORAGE_SOURCE})

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})