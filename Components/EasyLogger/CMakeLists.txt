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
        )


#
#add_executable(${PROJECT_NAME} ${FILES})
#
#target_include_directories(${PROJECT_NAME} PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/easylogger/inc
#        )
#
#target_link_libraries(${PROJECT_NAME}
#        pico_stdlib
#        )
