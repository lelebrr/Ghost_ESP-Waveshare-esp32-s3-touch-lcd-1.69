#include "smartwatch_screen.h"
#include "hardware_drivers/sensors.h"
#include "hardware_drivers/pmu.h"

lv_obj_t *smartwatch_screen;
static lv_obj_t *time_label;
static lv_obj_t *battery_label;

static void update_task(lv_timer_t *timer) {
    // Update time
    lv_label_set_text(time_label, rtc_get_time());

    // Update battery
    char buf[32];
    sprintf(buf, "Battery: %.2fV", pmu_get_battery_voltage());
    lv_label_set_text(battery_label, buf);
}

void smartwatch_screen_init() {
    smartwatch_screen = lv_obj_create(NULL);

    time_label = lv_label_create(smartwatch_screen);
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, -20);
    lv_obj_set_style_text_font(time_label, &lv_font_montserrat_32, 0);

    battery_label = lv_label_create(smartwatch_screen);
    lv_obj_align(battery_label, LV_ALIGN_CENTER, 0, 20);
    lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_16, 0);

    lv_timer_create(update_task, 1000, NULL);
}
