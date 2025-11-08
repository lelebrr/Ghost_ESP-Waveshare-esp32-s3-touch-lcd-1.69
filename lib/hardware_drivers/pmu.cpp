#include "pmu.h"
#include "board_config.h"
#include <Arduino.h>
#include <Wire.h>

static float battery_voltage = 4.2;

void pmu_init() {
    // This would initialize the AXP2101 using XPowersLib
    Wire.begin(I2C_SDA, I2C_SCL);
}

float pmu_get_battery_voltage() {
    battery_voltage -= 0.0001; // Simulate slower discharge
    if (battery_voltage < 3.0) {
        battery_voltage = 4.2;
    }
    return battery_voltage;
}
