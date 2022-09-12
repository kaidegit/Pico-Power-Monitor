//
// Created by yekai on 2022/9/11.
//

#ifndef PICO_POWER_MONITOR_INA226_H
#define PICO_POWER_MONITOR_INA226_H

#include <cstdint>
#include "elog.h"

class INA226 {
public:
    INA226(uint8_t _addr = 0x40) : addr(_addr) {};

    ~INA226() = default;

    void init();

    void SetConfig(uint8_t average_time = 0x00, uint8_t vbus_conv_time = 0x04,
                   uint8_t vshunt_conv_time = 0x04, uint8_t mode = 0x07);

    void SetCalibration();

    int32_t GetVoltage() const;

    int32_t GetShuntVoltage() const;

    int32_t GetCurrent() const;

private:
    uint8_t addr;

    float current_LSB;           // 电流分辨率mA
    float voltage_LSB = 1.25;    // 电压分辨率1.25mV

    uint8_t ReadU8(uint8_t reg_addr) const;

    uint16_t ReadU16(uint8_t reg_addr) const;

    void WriteU8(uint8_t reg_addr, uint8_t value) const;

    void WriteU16(uint8_t reg_addr, uint16_t value) const;
};

#endif //PICO_POWER_MONITOR_INA226_H
