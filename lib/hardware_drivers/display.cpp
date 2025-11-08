#include "display.h"
#include "board_config.h"

LGFX::LGFX(void) {
    _bus.config({
        (int8_t)LCD_SCLK, (int8_t)LCD_SDIO0, (int8_t)LCD_SDIO1, (int8_t)LCD_SDIO2, (int8_t)LCD_SDIO3,
    });
    _panel.bus(&_bus);
    _panel.config({
        (int8_t)LCD_CS,
        (uint8_t)1,    // EXIO
        false,         // Use CS
    });
    setPanel(&_panel);
}

LGFX gfx;

// LVGL buffer
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[TFT_WIDTH * 10];
static lv_disp_drv_t disp_drv;

// Display flush callback
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    gfx.pushImage(area->x1, area->y1, w, h, (lgfx::rgb565_t *)color_p);
    lv_disp_flush_ready(disp_drv);
}

void display_init() {
    gfx.begin();

    // Initialize LVGL
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, TFT_WIDTH * 10);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
}
