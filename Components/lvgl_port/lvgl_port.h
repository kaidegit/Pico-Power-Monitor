//
// Created by yekai on 2022/9/15.
//

#ifndef PICO_POWER_MONITOR_LVGL_PORT_H
#define PICO_POWER_MONITOR_LVGL_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t lv_lock;

void lv_set_lock();

void lv_clr_lock();

#ifdef __cplusplus
}
#endif

#endif //PICO_POWER_MONITOR_LVGL_PORT_H
