#include <Arduino.h>
#include <lvgl.h>

// The main function from the original Ghost ESP firmware
extern "C" void app_main(void);

void setup() {
    Serial.begin(115200);

    // Call the original main function
    app_main();
}

void loop() {
    // Handle LVGL tasks
    lv_task_handler();
    delay(5);
}
