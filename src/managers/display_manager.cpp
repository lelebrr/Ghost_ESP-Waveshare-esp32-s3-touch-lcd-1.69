#include "managers/display_manager.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "managers/sd_card_manager.h"
#include "managers/settings_manager.h"
#include "managers/views/error_popup.h"
#include "managers/views/main_menu_screen.h"
#include "managers/views/options_screen.h"
#include "managers/views/terminal_screen.h"
#include <stdlib.h>

// New hardware drivers
#include "display.h"
#include "touch.h"


#define LVGL_TASK_PERIOD_MS 5
static const char *TAG = "DisplayManager";
DisplayManager dm = {.current_view = NULL, .previous_view = NULL};

lv_obj_t *status_bar;
lv_obj_t *wifi_label = NULL;
lv_obj_t *bt_label = NULL;
lv_obj_t *sd_label = NULL;
lv_obj_t *battery_label = NULL;

bool display_manager_init_success = false;

// --- Forward Declarations ---
static void lvgl_tick_task(void *pvParameters);


// --- Display Manager Initialization ---
void display_manager_init(void) {
    // Initialize new hardware drivers
    display_init();
    touch_init();

    display_manager_init_success = true;

    // Start LVGL tick task
    xTaskCreate(lvgl_tick_task, "LVGL Tick Task", 4096, NULL, 5, NULL);
}

// --- LVGL Tick Task ---
static void lvgl_tick_task(void *pvParameters) {
    while (1) {
        lv_tick_inc(LVGL_TASK_PERIOD_MS);
        vTaskDelay(pdMS_TO_TICKS(LVGL_TASK_PERIOD_MS));
    }
    vTaskDelete(NULL);
}
