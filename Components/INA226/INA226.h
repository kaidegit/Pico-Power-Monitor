//
// Created by yekai on 2022/9/11.
//

#ifndef PICO_POWER_MONITOR_INA226_H
#define PICO_POWER_MONITOR_INA226_H

#include <cstdint>
#include "elog.h"
#include "i2c_base.h"
#include "config.h"

class INA226 : public I2C_Base {
public:
    INA226(uint8_t _addr = 0x40) : I2C_Base(INA_I2C_NUM, _addr) {};

    void init();

    void SetConfig(uint8_t average_time = 0x02, uint8_t vbus_conv_time = 0x04,
                   uint8_t vshunt_conv_time = 0x04, uint8_t mode = 0x07);

    void SetCalibration();

    int32_t GetVoltage() const;

    int32_t GetShuntVoltage() const;

    int32_t GetCurrent() const;

private:
    float current_LSB = 0;           // 电流分辨率mA
    float voltage_LSB = 1.25;    // 电压分辨率1.25mV
};

#endif //PICO_POWER_MONITOR_INA226_H
