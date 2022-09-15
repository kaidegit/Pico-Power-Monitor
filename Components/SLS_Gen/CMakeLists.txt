file(GLOB FILES "*.c" "*.cpp")

add_library(SLS_Gen STATIC
        ${FILES}
        )

target_include_directories(SLS_Gen PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(SLS_Gen
        pico_stdlib
        Config
        lvgl_port
        lvgl
        )