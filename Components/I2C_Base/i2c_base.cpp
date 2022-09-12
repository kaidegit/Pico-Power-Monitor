//
// Created by yekai on 2022/9/12.
//

#include "i2c_base.h"

uint8_t I2C_Base::ReadU8(uint8_t reg_addr) const {
    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    i2c_write_blocking(i2c, addr, buf, 1, true);
    i2c_read_blocking(i2c, addr, buf, 1, false);
    return buf[0];
}

uint16_t I2C_Base::ReadU16(uint8_t reg_addr) const {
    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    i2c_write_blocking(i2c, addr, buf, 1, true);
    i2c_read_blocking(i2c, addr, buf, 2, false);
    return buf[0] << 8 | buf[1];
}

void I2C_Base::WriteU8(uint8_t reg_addr, uint8_t value) const {
    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    buf[1] = value;
    i2c_write_blocking(i2c, addr, buf, 2, false);
}

void I2C_Base::WriteU16(uint8_t reg_addr, uint16_t value) const {
    uint8_t buf[3] = {0};
    buf[0] = reg_addr;
    buf[1] = value >> 8;
    buf[2] = value & 0xFF;
    i2c_write_blocking(i2c, addr, buf, 3, false);
}
