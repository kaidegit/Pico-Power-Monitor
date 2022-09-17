/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "main.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "elog.h"
#include "config.h"
#include "INA226.h"
#include "Screen.h"
#include "lvgl_port.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ui.h"

static const char *TAG = "main";

auto ina = INA226();

void main_task(void *para) {
    ina.init();
    ina.SetConfig();
    ina.SetCalibration();

    while (1) {
        auto vol = ina.GetVoltage();
        auto cur = ina.GetCurrent();
        auto power = vol * cur;
        elog_i(TAG, "get voltage : %dmv, current : %dma, power : %dmw",
               vol, cur, power);
        // TODO 考虑负数
        // TODO 考虑两位整数
        // TODO 功率考虑多位整数
        // TODO 小数位
        // 最后一位直接通过均值滤波取得？
        char vol_buf[32];
        snprintf(vol_buf, sizeof(vol_buf), "%01d.%03dV", vol / 1000, vol % 1000);
        char cur_buf[32];
        snprintf(cur_buf, sizeof(cur_buf), "%01d.%03dA", cur / 1000, cur % 1000);
        char power_buf[32];
        snprintf(power_buf, sizeof(power_buf), "%02d.%03dW", power / 1000000, (power % 1000000) / 1000);
        xSemaphoreTake(lv_lock, portMAX_DELAY);
        lv_label_set_text(ui_Voltage, vol_buf);
        lv_label_set_text(ui_Current, cur_buf);
        lv_label_set_text(ui_Power, power_buf);
        xSemaphoreGive(lv_lock);
        vTaskDelay(200);
    }
}

extern "C" void log_entry(void *para);

void lvgl_thread(void *para);

void vApplicationStackOverflowHook(
        TaskHandle_t xTask, char *pcTaskName) {
    elog_e(TAG, "stack over flow!");
}

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

    xTaskCreate(
            main_task,
            "main",
            1024,
            nullptr,
            4,
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

    xTaskCreate(
            lvgl_thread,
            "lvgl",
            4096,
            nullptr,
            5,
            nullptr
    );

    vTaskStartScheduler();
//  ----------- should not run to here -----------
    while (true) {
        elog_i("ERROR", "FreeRTOS Crashed");
        sleep_ms(1000);
    }
}
