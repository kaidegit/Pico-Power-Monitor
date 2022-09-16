file(GLOB FILES "*.c" "*.cpp")

add_library(Screen STATIC
        ${FILES}
        )

target_include_directories(Screen PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(Screen
        pico_stdlib
        Config
        hardware_spi
        hardware_dma
        hardware_irq
        lvgl_port
        EasyLogger
        )