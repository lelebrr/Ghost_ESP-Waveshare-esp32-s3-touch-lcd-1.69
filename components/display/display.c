#include "display.h"
#include "board_config.h"
#include <stdio.h>

// LVGL buffer
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[TFT_WIDTH * 10];
static lv_disp_drv_t disp_drv;

// Display flush callback
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    printf("Flushing display buffer...\n");
    // This would send the buffer to the display
    lv_disp_flush_ready(disp_drv);
}

void display_init() {
    // This would initialize the display hardware

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
