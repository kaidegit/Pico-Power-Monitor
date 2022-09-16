//
// Created by yekai on 2022/9/15.
//

#include "config.h"
#include "lvgl_port.h"
#include "lvgl.h"
#include "Screen.h"
#include "hardware/spi.h"
#include "ui.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

auto screen = Screen();
uint8_t lvgl_draw_buff1[2560] = {0};
uint8_t lvgl_draw_buff2[2560] = {0};

SemaphoreHandle_t lv_lock = NULL;
SemaphoreHandle_t screen_dma_idle = NULL;

void lv_lock_init() {
    lv_lock = xSemaphoreCreateBinary();
    xSemaphoreGive(lv_lock);
}

void lv_set_lock() {
    xSemaphoreTake(lv_lock, portMAX_DELAY);
}

void lv_clr_lock() {
    xSemaphoreGive(lv_lock);
}

void screen_dma_handler() {
    dma_hw->ints1 = 1u << screen.screen_dma_chan;
    xSemaphoreGiveFromISR(screen_dma_idle, NULL);
    // wait until fifo is clear.
    while (spi_is_busy(SCREEN_SPI_NUM));
    ST7735_Unselect();
}

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    // 等待上次传输完成
    xSemaphoreTake(screen_dma_idle, portMAX_DELAY);
    /* 启动新的传输 */
    auto width(area->x2 - area->x1 + 1), height(area->y2 - area->y1 + 1);
    screen.DMAShow(area->x1, area->y1, width, height, (const uint16_t *) color_p);
    /* 通知lvgl传输已完成 */
    lv_disp_flush_ready(disp_drv);
}

void lvgl_thread(void *para) {
    lv_lock_init();
    lv_set_lock();

    lv_init();
    screen.init();
    screen.initDMA();
    screen_dma_idle = xSemaphoreCreateBinary();
    xSemaphoreGive(screen_dma_idle);

    // 向lvgl注册缓冲区
    static lv_disp_draw_buf_t draw_buf_dsc;
    lv_disp_draw_buf_init(
            &draw_buf_dsc,
            lvgl_draw_buff1, lvgl_draw_buff2,
            sizeof(lvgl_draw_buff1) / sizeof(lv_color_t));

    /* 创建并初始化用于在lvgl中注册显示设备的结构 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screen.width;
    disp_drv.ver_res = screen.height;
    disp_drv.draw_buf = &draw_buf_dsc;
    disp_drv.flush_cb = disp_flush;
    lv_disp_drv_register(&disp_drv);

//    lv_create_tick();

    ui_init();

    lv_clr_lock();

    while (1) {
        lv_set_lock();
        lv_task_handler();
        lv_clr_lock();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}