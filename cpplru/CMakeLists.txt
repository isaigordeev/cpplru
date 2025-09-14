# ===============================
# Add C++ libraries
# ===============================
add_subdirectory(lru)
add_subdirectory(storage)
add_subdirectory(auth)
add_subdirectory(concurrency)

# ===============================
# Main executable for C++
# ===============================
add_executable(main
        main.cpp
        ${LRU_SOURCES}
        ${AUTH_SOURCES}
        ${STORAGE_SOURCES}
        ${CONC_SOURCES}
        )

target_include_directories(main PRIVATE
        ${CMAKE_SOURCE_DIR}/cpplru/lru
        ${CMAKE_SOURCE_DIR}/cpplru/auth
        ${CMAKE_SOURCE_DIR}/cpplru/storage
        ${CMAKE_SOURCE_DIR}/cpplru/concurrency
        )

target_compile_options(main PRIVATE -fsanitize=address -g)
target_link_options(main PRIVATE -fsanitize=address)
target_link_libraries(main PRIVATE lru auth storage concurrency)