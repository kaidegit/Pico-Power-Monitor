//
// Created by yekai on 2022/9/12.
//

#ifndef PICO_POWER_MONITOR_SCREEN_H
#define PICO_POWER_MONITOR_SCREEN_H

#include "ST7735.h"

class Screen {
public:
    Screen() = default;

    ~Screen() = default;

    void init();

    void Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
        ST7735_FillRectangle(x, y, w, h, color);
    }

};


#endif //PICO_POWER_MONITOR_SCREEN_H
