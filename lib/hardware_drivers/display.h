#ifndef DISPLAY_H
#define DISPLAY_H

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "board_config.h"

class LGFX : public lgfx::LGFX_Device
{
public:
    lgfx::Bus_QSPI _bus;
    lgfx::Panel_Device _panel;
    lgfx::Touch_FT5x06 _touch; // FT5x06 is often compatible with FT3168

    LGFX(void)
    {
        // Bus configuration
        _bus.config({
            .spi_host = SPI2_HOST,
            .spi_sclk = LCD_SCLK,
            .spi_mosi = LCD_SDIO0,
            .spi_miso = LCD_SDIO1,
            .spi_quadwp = LCD_SDIO2,
            .spi_quadhd = LCD_SDIO3,
            .freq_write = 80000000,
            .freq_read = 16000000,
        });
        _panel.setBus(&_bus);

        // Panel configuration
        _panel.config({
            .pin_cs = LCD_CS,
            .pin_rst = -1,
            .pin_busy = -1,
            .panel_width = TFT_WIDTH,
            .panel_height = TFT_HEIGHT,
            .offset_x = 0,
            .offset_y = 0,
            .bus_shared = false,
        });
        setPanel(&_panel);

        // Touch configuration
        _touch.config({
            .i2c_port = I2C_NUM_0,
            .i2c_addr = 0x38, // Standard FT5x06 address, might be the same
            .pin_sda = I2C_SDA,
            .pin_scl = I2C_SCL,
            .freq = 400000,
            .x_min = 0,
            .x_max = TFT_WIDTH,
            .y_min = 0,
            .y_max = TFT_HEIGHT,
        });
        _panel.setTouch(&_touch);
    }
};

extern LGFX gfx;

void display_init();
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

#endif // DISPLAY_H
