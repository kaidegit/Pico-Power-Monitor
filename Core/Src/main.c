/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "main.h"
#include "pico/stdlib.h"

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    uart_init(LOG_UART_NUM, 115200);
    gpio_set_function(LOG_UART_TX, GPIO_FUNC_UART);

    while (true) {
        uart_puts(LOG_UART_NUM, " Hello, UART!\n");
        sleep_ms(1000);
    }
}
