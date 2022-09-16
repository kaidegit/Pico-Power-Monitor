/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */

#include <elog.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "config.h"
#include "hardware/timer.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "freertos.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t elog_lock;
SemaphoreHandle_t elog_async;
SemaphoreHandle_t elog_dma_lock;

int log_dma_chan;
dma_channel_config log_dma_config;

void dma_handler() {
    dma_hw->ints0 = 1u << log_dma_chan;
    xSemaphoreGiveFromISR(elog_dma_lock, NULL);
}

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    elog_lock = xSemaphoreCreateBinary();
    xSemaphoreGive(elog_lock);

    elog_async = xSemaphoreCreateBinary();
    xSemaphoreGive(elog_async);
    xSemaphoreTake(elog_async, 0);

    elog_dma_lock = xSemaphoreCreateBinary();
    xSemaphoreGive(elog_dma_lock);

    log_dma_chan = dma_claim_unused_channel(true);
    log_dma_config = dma_channel_get_default_config(log_dma_chan);
    channel_config_set_transfer_data_size(&log_dma_config, DMA_SIZE_8);
    channel_config_set_read_increment(&log_dma_config, true);
    channel_config_set_write_increment(&log_dma_config, false);
    channel_config_set_dreq(&log_dma_config, DREQ_UART0_TX);

    dma_channel_set_irq0_enabled(log_dma_chan, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    dma_channel_configure(
            log_dma_chan,          // Channel to be configured
            &log_dma_config,            // The configuration we just created
            &uart_get_hw(LOG_UART_NUM)->dr,         // The initial write address
            NULL,           // The initial read address
            0, // Number of transfers; in this case each is 1 byte.
            false           // Start immediately.
    );

    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void) {
    /* add your code here */
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    dma_channel_set_read_addr(log_dma_chan, log, false);
    dma_channel_set_trans_count(log_dma_chan, size, true);

//    dma_channel_wait_for_finish_blocking(log_dma_chan);
//    uart_write_blocking(LOG_UART_NUM, (const uint8_t *)log, size);
//    xSemaphoreGive(elog_dma_lock);
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    xSemaphoreTake(elog_lock, portMAX_DELAY);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    xSemaphoreGive(elog_lock);
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    static char cur_system_time[16] = "";
    snprintf(cur_system_time, 16, "%lu", time_us_32() / 1000);
    return cur_system_time;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    return "";
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    return "";
}

void elog_async_output_notice(void) {
    xSemaphoreGive(elog_async);
}

void log_entry(void *para) {
    size_t get_log_size = 0;
    static char poll_get_buf[ELOG_LINE_BUF_SIZE - 4];

    if (elog_port_init() != ELOG_NO_ERR) {
        goto fail;
    }
    while (xSemaphoreTake(elog_async, portMAX_DELAY) == pdTRUE) {
        while (xSemaphoreTake(elog_dma_lock, portMAX_DELAY) == pdTRUE) {
            get_log_size = elog_async_get_line_log(poll_get_buf, sizeof(poll_get_buf));
            if (get_log_size) {
                elog_port_output(poll_get_buf, get_log_size);
            } else {
                xSemaphoreGive(elog_dma_lock);
                break;
            }
        }
    }

    fail:
    vTaskDelete(NULL);
}