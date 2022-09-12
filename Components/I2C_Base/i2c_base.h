//
// Created by yekai on 2022/9/12.
//

#ifndef PICO_POWER_MONITOR_I2C_BASE_H
#define PICO_POWER_MONITOR_I2C_BASE_H

#include <hardware/i2c.h>
#include <cstdint>

class I2C_Base {
public:
    I2C_Base(i2c_inst_t *_i2c, uint8_t _addr) : i2c(_i2c), addr(_addr) {};

    ~I2C_Base() = default;

    i2c_inst_t *i2c;
    uint8_t addr;

    uint8_t ReadU8(uint8_t reg_addr) const;

    uint16_t ReadU16(uint8_t reg_addr) const;

    void WriteU8(uint8_t reg_addr, uint8_t value) const;

    void WriteU16(uint8_t reg_addr, uint16_t value) const;
};

#endif //PICO_POWER_MONITOR_I2C_BASE_H
