//
// Created by yekai on 2022/9/11.
//

#include <hardware/gpio.h>
#include "INA226.h"
#include "INA226_reg_table.h"
#include "config.h"
#include "hardware/i2c.h"

static const char *TAG = "INA226";

void INA226::init() {
    i2c_init(INA_I2C_NUM, 100 * 1000);
    gpio_set_function(INA_SDA, GPIO_FUNC_I2C);
    gpio_set_function(INA_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(INA_SDA);
    gpio_pull_up(INA_SCL);
}

void INA226::SetConfig() {

}

void INA226::SetCalibration() {
    auto rshunt = 0.005f;     // 分压电阻5mohm
    auto imax = 5.0f;                  // 最大电流5A
    current_LSB = imax / 32767.0f * 1000;     // 电流分辨率mA
    auto val = 5.12f / (current_LSB * rshunt);
    WriteU16(INA_CALIBRATION_REG, uint16_t(val));
}


int32_t INA226::GetVoltage() const {
    auto mvol = float(int16_t(ReadU16(INA_BUS_VOLTAGE_REG)));
    mvol = mvol * voltage_LSB;
//    mvol = mvol + (mvol >> 2);
    auto ret = int32_t(mvol);
    elog_i(TAG, "get voltage : %dmv", ret);
    return ret;
}

int32_t INA226::GetShuntVoltage() const {
    auto uvol = int16_t(ReadU16(INA_SHUNT_VOLTAGE_REG));
    uvol = uvol * 25 / 10;
    elog_i(TAG, "get shunt voltage : %duv", uvol);
    return uvol;
}

int32_t INA226::GetCurrent() const {
    auto mamp = float(int16_t(ReadU16(INA_CURRENT_REG)));
    mamp *= current_LSB;
    auto ret = int32_t(mamp);
    elog_i(TAG, "get current : %dmA", ret);
    return ret;
}

uint8_t INA226::ReadU8(uint8_t reg_addr) const {
    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    i2c_write_blocking(INA_I2C_NUM, addr, buf, 1, true);
    i2c_read_blocking(INA_I2C_NUM, addr, buf, 1, false);
    return buf[0];
}

uint16_t INA226::ReadU16(uint8_t reg_addr) const {
    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    i2c_write_blocking(INA_I2C_NUM, addr, buf, 1, true);
    i2c_read_blocking(INA_I2C_NUM, addr, buf, 2, false);
    return buf[0] << 8 | buf[1];
}

void INA226::WriteU8(uint8_t reg_addr, uint8_t value) const {
    uint8_t buf[2] = {0};
    buf[0] = reg_addr;
    buf[1] = value;
    i2c_write_blocking(INA_I2C_NUM, addr, buf, 2, false);
}

void INA226::WriteU16(uint8_t reg_addr, uint16_t value) const {
    uint8_t buf[3] = {0};
    buf[0] = reg_addr;
    buf[1] = value >> 8;
    buf[2] = value & 0xFF;
    i2c_write_blocking(INA_I2C_NUM, addr, buf, 3, false);
}



