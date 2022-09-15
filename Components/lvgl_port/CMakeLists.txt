file(GLOB FILES "*.c" "*.cpp")

add_library(lvgl_port STATIC
        ${FILES}
        )

target_include_directories(lvgl_port PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(lvgl_port
        pico_stdlib
        Config
        Screen
        lvgl
        SLS_Gen
        FreeRTOS-Kernel-Heap4
        )