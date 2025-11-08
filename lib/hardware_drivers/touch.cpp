#include "touch.h"
#include "board_config.h"
#include <Arduino.h>
#include <Wire.h>
#include "display.h" // To get the gfx object

extern LGFX gfx;

static void touch_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    uint16_t touchX, touchY;
    bool touched = gfx.getTouch(&touchX, &touchY);

    if (!touched) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

void touch_init() {
    // This assumes LovyanGFX is configured for touch as well.
    // The actual touch controller would be initialized here.
    // Wire.begin(I2C_SDA, I2C_SCL);

    // Initialize LVGL input device
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touch_read;
    lv_indev_drv_register(&indev_drv);
}
