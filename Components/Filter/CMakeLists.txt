file(GLOB FILES "*.c" "*.cpp")

add_library(Filter STATIC
        ${FILES}
        )

target_include_directories(Filter PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(Filter
        pico_stdlib
        )