//
// Created by yekai on 2022/9/12.
//

#include <hardware/gpio.h>
#include "hardware/spi.h"
#include "Screen.h"
#include "ST7735.h"
#include "config.h"

void Screen::init() {
    gpio_init(SCREEN_CS);
    gpio_set_dir(SCREEN_CS, GPIO_OUT);
    gpio_init(SCREEN_DC);
    gpio_set_dir(SCREEN_DC, GPIO_OUT);
    gpio_init(SCREEN_RES);
    gpio_set_dir(SCREEN_RES, GPIO_OUT);

    spi_init(SCREEN_SPI_NUM, 10 * 1000 * 1000);
    gpio_set_function(SCREEN_CLK,GPIO_FUNC_SPI);
    gpio_set_function(SCREEN_MOSI, GPIO_FUNC_SPI);

    ST7735_Init();
    Fill(0, 0, 160, 80, ST7735_WHITE);
}
