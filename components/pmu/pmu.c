#include "pmu.h"
#include "board_config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static float battery_voltage = 4.2;

void pmu_init() {
    // This would initialize the AXP2101
}

float pmu_get_battery_voltage() {
    battery_voltage -= 0.001;
    if (battery_voltage < 3.0) {
        battery_voltage = 4.2;
    }
    return battery_voltage;
}
