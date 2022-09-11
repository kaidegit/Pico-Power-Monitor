add_library(Config STATIC
        config.c
        )

target_include_directories(Config PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )