file(GLOB FILES "*.c" "*.cpp")

add_library(I2C_Base STATIC
        ${FILES}
        )

target_include_directories(I2C_Base PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(I2C_Base
        pico_stdlib
        hardware_i2c
        )