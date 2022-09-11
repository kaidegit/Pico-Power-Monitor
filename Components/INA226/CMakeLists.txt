file(GLOB FILES "*.c" "*.cpp")

add_library(INA226 STATIC
        ${FILES}
        )

target_include_directories(INA226 PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(INA226
        Config
        pico_stdlib
        EasyLogger
        hardware_i2c
        )