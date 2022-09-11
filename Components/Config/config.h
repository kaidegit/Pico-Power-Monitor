//
// Created by yekai on 2022/9/11.
//

#ifndef PICO_POWER_MONITOR_CONFIG_H
#define PICO_POWER_MONITOR_CONFIG_H

// LOG
#define LOG_UART_NUM uart0
#define LOG_UART_TX 16
#define LOG_UART_RX -1

// INA226
#define INA_I2C_NUM i2c0
#define INA_SDA 24
#define INA_SCL 25

// FUSB302
#define FUSB_I2C_NUM i2c1
#define FUSB_SDA 22
#define FUSB_SCL 23

#endif //PICO_POWER_MONITOR_CONFIG_H
