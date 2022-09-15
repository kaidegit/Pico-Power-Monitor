/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "main.h"
#include "pico/stdlib.h"
#include "elog.h"
#include "config.h"
#include "INA226.h"
#include "Screen.h"
#include "FreeRTOS.h"
#include "task.h"

static const char *TAG = "main";

auto ina = INA226();

auto screen = Screen();

void main_task(void *para) {
    ina.init();
    ina.SetConfig();
    ina.SetCalibration();

    while (1) {
        ina.GetVoltage();
//        ina.GetShuntVoltage();
        ina.GetCurrent();
        vTaskDelay(1000);
    }
}

extern "C" void log_entry(void *para);

int main() {

    uart_init(LOG_UART_NUM, 1000000);
    gpio_set_function(LOG_UART_TX, GPIO_FUNC_UART);

    elog_init();

    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_P_INFO));
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_P_INFO));

    elog_start();

    screen.init();

    xTaskCreate(
            main_task,
            "main",
            1024,
            nullptr,
            5,
            nullptr
            );

    xTaskCreate(
            log_entry,
            "log",
            1024,
            nullptr,
            6,
            nullptr
            );

    vTaskStartScheduler();
//  ----------- should not run to here -----------
    while (true) {
        elog_i("ERROR", "FreeRTOS Crashed");
        sleep_ms(1000);
    }
}
