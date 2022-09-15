cmake_minimum_required(VERSION 3.17)

include(pico_sdk_import.cmake)

project(pico-power-monitor)

set(FREERTOS_CONFIG_FILE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc)

include(Components/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

#message("freertos config is here ${FREERTOS_CONFIG_FILE_DIRECTORY}")

#set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Components/lvgl_port)

add_subdirectory(Core)
add_subdirectory(Components/EasyLogger)
add_subdirectory(Components/Config)
add_subdirectory(Components/I2C_Base)
add_subdirectory(Components/INA226)
add_subdirectory(Components/Screen)
add_subdirectory(Components/lvgl)
add_subdirectory(Components/lvgl_port)
add_subdirectory(Components/SLS_Gen)