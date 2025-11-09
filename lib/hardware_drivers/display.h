#ifndef DISPLAY_H
#define DISPLAY_H

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "board_config.h"

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Bus_QSPI _bus_instance;
    lgfx::Panel_SH8601 _panel_instance;
    lgfx::Touch_FT5x06 _touch_instance;

public:
    LGFX(void)
    {
        {
            auto cfg = _bus_instance.config();
            cfg.spi_host = SPI2_HOST;
            cfg.spi_sclk = LCD_SCLK;
            cfg.spi_mosi = LCD_SDIO0;
            cfg.spi_miso = LCD_SDIO1;
            cfg.spi_quadwp = LCD_SDIO2;
            cfg.spi_quadhd = LCD_SDIO3;
            cfg.freq_write = 80000000;
            cfg.freq_read = 16000000;
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs = LCD_CS;
            cfg.pin_rst = -1;
            cfg.pin_busy = -1;
            cfg.panel_width = TFT_WIDTH;
            cfg.panel_height = TFT_HEIGHT;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.bus_shared = false;
            _panel_instance.config(cfg);
        }

        {
            auto cfg = _touch_instance.config();
            cfg.i2c_port = 0;
            cfg.i2c_addr = 0x38;
            cfg.pin_sda = I2C_SDA;
            cfg.pin_scl = I2C_SCL;
            cfg.freq = 400000;
            cfg.x_min = 0;
            cfg.x_max = TFT_WIDTH;
            cfg.y_min = 0;
            cfg.y_max = TFT_HEIGHT;
            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }

        setPanel(&_panel_instance);
    }
};

extern LGFX gfx;

void display_init();
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

#endif // DISPLAY_H
