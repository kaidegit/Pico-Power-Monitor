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

void INA226::SetConfig(uint8_t average_time /*= 0x00*/, uint8_t vbus_conv_time /*= 0x04*/,
                       uint8_t vshunt_conv_time /*= 0x04*/, uint8_t mode /*= 0x07*/) {
    // 避免参数错误
    average_time &= 0x07;
    vbus_conv_time &= 0x07;
    vshunt_conv_time &= 0x07;
    mode &= 0x07;

    uint16_t config =
            0x4000 |
            average_time << 9 |
            vbus_conv_time << 6 |
            vshunt_conv_time << 3 |
            mode;

    WriteU16(INA_CONFIG_REG, config);
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


