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
#include "filter.h"

static const char *TAG = "main";

auto ina = INA226();

void main_task(void *para) {
    ina.init();
    ina.SetConfig();
    ina.SetCalibration();

    auto vol_filter = Filter();
    auto cur_filter = Filter();

    auto cur_direction_state = uint8_t(0);

    while (1) {
        auto vol = ina.GetVoltage();
        auto cur = ina.GetCurrent();
        vol = vol_filter.out_10x(vol);  // unit:0.1mV 0.0001V
        cur = cur_filter.out_10x(cur);  // unit:0.1mA 0.0001A
        // 在1ma内忽略
        if ((-10 <= cur) && (cur <= 10)) {
            cur = 0;
        }
        auto negative = cur < 0;
        cur = negative ? -cur : cur;

        auto power = int32_t(uint64_t(vol) * cur / 10000);   // unit:0.1mW 0.0001W
        elog_i(TAG, "get voltage : %dmv, current : %dma, power : %dmw",
               vol / 10, cur / 10, power / 10);
        // 最后一位直接通过滑动均值滤波取得
        char vol_buf[32];
        auto vol_int = vol / 10000;
        auto vol_dec = vol % 10000;
        if (vol_int < 10) {
            snprintf(vol_buf, sizeof(vol_buf), "%01d.%04dV", vol_int, vol_dec);
        } else if (vol_int < 100) {
            snprintf(vol_buf, sizeof(vol_buf), "%02d.%03dV", vol_int, vol_dec / 10);
        }

        char cur_buf[32];
        auto cur_int = cur / 10000;
        auto cur_dec = cur % 10000;
        if (cur_int < 10) {
            snprintf(cur_buf, sizeof(cur_buf), "%01d.%04dA", cur_int, cur_dec);
        } else if (cur_int < 100) {
            snprintf(cur_buf, sizeof(cur_buf), "%02d.%03dA", cur_int, cur_dec / 10);
        }

        char power_buf[32];
        auto power_int = power / 10000;
        auto power_dec = power % 10000;
        if (power_int < 10) {
            snprintf(power_buf, sizeof(power_buf), "%01d.%04dW", power_int, power_dec);
        } else if (power_int < 100) {
            snprintf(power_buf, sizeof(power_buf), "%02d.%03dW", power_int, power_dec / 10);
        } else if (power_int < 1000) {
            snprintf(power_buf, sizeof(power_buf), "%03d.%02dW", power_int, power_dec / 100);
        }

        xSemaphoreTake(lv_lock, portMAX_DELAY);
        lv_label_set_text(ui_Voltage, vol_buf);
        lv_label_set_text(ui_Current, cur_buf);
        lv_label_set_text(ui_Power, power_buf);
        switch (cur_direction_state) {
            case 0 ... 5:
                lv_label_set_text(ui_CurDirection, negative ? ">---" : "---<");
                cur_direction_state++;
                break;
            case 6 ... 10:
                lv_label_set_text(ui_CurDirection, negative ? "->--" : "--<-");
                cur_direction_state++;
                break;
            case 11 ... 15:
                lv_label_set_text(ui_CurDirection, negative ? "-->-" : "-<--");
                cur_direction_state++;
                break;
            case 16 ... 20:
                lv_label_set_text(ui_CurDirection, negative ? "--->" : "<---");
                cur_direction_state++;
                break;
            default:
                cur_direction_state = 0;
                break;
        }
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
