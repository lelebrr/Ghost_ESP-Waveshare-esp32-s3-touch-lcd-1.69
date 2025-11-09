#include "display.h"
#include "board_config.h"

// Instantiate the custom graphics driver
LGFX gfx;

// LVGL buffer and display driver
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[TFT_WIDTH * 40]; // Increased buffer size for better performance
static lv_disp_drv_t disp_drv;

// LVGL display flush callback
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    gfx.startWrite();
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.writePixels((lgfx::rgb565_t *)color_p, w * h);
    gfx.endWrite();
    lv_disp_flush_ready(disp_drv);
}

// Initialize the display and LVGL
void display_init()
{
    gfx.begin();
    gfx.fillScreen(TFT_BLACK);

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, sizeof(buf1) / sizeof(lv_color_t));

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
}
