# 一个基于RP2040的U表

开个新坑，做个U表，暂时还未完工，欢迎issue和pr，不论是对代码、对PCB还是对功能的。

## 硬件开源地址

[立创开源地址](https://oshwhub.com/baobaoa/usb-c-pd-power-monitor)

## TODO List

- [x] EasyLogger移植
- [x] Log通过DMA发送
- [x] FreeRTOS移植
- [x] INA226
- [ ] FUSB302
- [x] TFT-LCD
- [x] LVGL
- [ ] 诱骗输出

## 三方库许可说明

* EasyLogger：使用MIT协议开源
* Screen：基于仓库`afiskon/stm32-st7735`二次开发。此仓库使用了部分`Adafruit ST7735 library`的初始化代码。这两个仓库均以MIT开源
* FreeRTOS：主仓库使用MIT协议开源，树莓派团队适配部分使用BSD协议开源
* LVGL：使用MIT协议开源



