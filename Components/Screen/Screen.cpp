//
// Created by yekai on 2022/9/12.
//

#include <hardware/gpio.h>
#include "hardware/spi.h"
#include "Screen.h"
#include "ST7735.h"
#include "config.h"

void Screen::init() {
    gpio_init(SCREEN_CS);
    gpio_set_dir(SCREEN_CS, GPIO_OUT);
    gpio_init(SCREEN_DC);
    gpio_set_dir(SCREEN_DC, GPIO_OUT);
    gpio_init(SCREEN_RES);
    gpio_set_dir(SCREEN_RES, GPIO_OUT);

    spi_init(SCREEN_SPI_NUM, 1 * 1000 * 1000);
    gpio_set_function(SCREEN_CLK,GPIO_FUNC_SPI);
    gpio_set_function(SCREEN_MOSI, GPIO_FUNC_SPI);

    ST7735_Init();
//    Fill(0, 0, width, height, ST7735_WHITE);
}

extern void screen_dma_handler();

void Screen::initDMA() {
    screen_dma_chan = dma_claim_unused_channel(true);
    screen_dma_config = dma_channel_get_default_config(screen_dma_chan);
    channel_config_set_transfer_data_size(&screen_dma_config, DMA_SIZE_8);
    channel_config_set_read_increment(&screen_dma_config, true);
    channel_config_set_write_increment(&screen_dma_config, false);
    channel_config_set_dreq(&screen_dma_config, DREQ_SPI0_TX);

    dma_channel_set_irq1_enabled(screen_dma_chan, true);
    irq_set_exclusive_handler(DMA_IRQ_1, screen_dma_handler);
    irq_set_enabled(DMA_IRQ_1, true);

    dma_channel_configure(
            screen_dma_chan,          // Channel to be configured
            &screen_dma_config,            // The configuration we just created
            &spi_get_hw(SCREEN_SPI_NUM)->dr,           // The initial write address
            NULL,           // The initial read address
            0, // Number of transfers; in this case each is 1 byte.
            false           // Start immediately.
    );
}