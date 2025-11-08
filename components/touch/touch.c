#include "touch.h"
#include "board_config.h"
#include <stdlib.h>

static void touch_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    // Simulate a random touch every 10 calls
    if (rand() % 10 == 0) {
        data->point.x = rand() % TFT_WIDTH;
        data->point.y = rand() % TFT_HEIGHT;
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

void touch_init() {
    // This would initialize the touch controller

    // Initialize LVGL input device
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touch_read;
    lv_indev_drv_register(&indev_drv);
}
