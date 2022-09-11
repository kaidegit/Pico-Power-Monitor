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

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */

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
    uart_write_blocking(LOG_UART_NUM, (const uint8_t *)log, size);
//    HAL_UART_Transmit_DMA(&huart4, (uint8_t *) log, size);
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
//    osSemaphoreAcquire(elog_lockHandle, osWaitForever);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
//    osSemaphoreRelease(elog_lockHandle);
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    static char cur_system_time[16] = "";
//    snprintf(cur_system_time, 16, "%lu", osKernelGetTickCount());
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

//void elog_async_output_notice(void) {
//    osSemaphoreRelease(elog_asyncHandle);
//}
//
//void log_entry(void *para) {
//    size_t get_log_size = 0;
//    static char poll_get_buf[ELOG_LINE_BUF_SIZE - 4];
//
//    if (elog_port_init() != ELOG_NO_ERR) {
//        goto fail;
//    }
//
////    elog_init();
////
////    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL & ~ELOG_FMT_P_INFO);
////    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
////    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
////    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
////    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_P_INFO));
////    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~(ELOG_FMT_FUNC | ELOG_FMT_P_INFO));
////
////    elog_start();
//
//    while (1) {
//        if (osOK ==
//            osSemaphoreAcquire(elog_asyncHandle, osWaitForever)) {
//            while (1) {
//                if (osOK ==
//                    osSemaphoreAcquire(elog_dma_lockHandle, osWaitForever)) {
//                    get_log_size = elog_async_get_line_log(poll_get_buf, sizeof(poll_get_buf));
//                    if (get_log_size) {
//                        elog_port_output(poll_get_buf, get_log_size);
//                    } else {
//                        osSemaphoreRelease(elog_dma_lockHandle);
//                        break;
//                    }
//                }
//            }
//        }
//
//    }
//
//    fail:
//    osThreadExit();
//
//}