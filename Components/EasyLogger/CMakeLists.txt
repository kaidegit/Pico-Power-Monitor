file(GLOB FILES "easylogger/src/*.c" "easylogger/port/*.c")

add_library(EasyLogger STATIC
        ${FILES}
        )

target_include_directories(EasyLogger PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/easylogger/inc
        )

target_link_libraries(EasyLogger
        Config
        pico_stdlib
        FreeRTOS-Kernel-Heap4
        hardware_dma
        hardware_irq
        )