#ifndef PMU_H
#define PMU_H

#include "freertos/FreeRTOS.h"

// Initialize the Power Management Unit
void pmu_init();

// Get the battery voltage
float pmu_get_battery_voltage();

#endif // PMU_H
