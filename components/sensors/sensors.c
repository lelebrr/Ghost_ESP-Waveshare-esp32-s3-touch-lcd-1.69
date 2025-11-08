#include "sensors.h"
#include "board_config.h"
#include <time.h>
#include <stdlib.h>

void sensors_init() {
    // This would initialize the sensors
    srand(time(NULL));
}

int imu_read_gesture() {
    return rand() % 3; // Simulate 3 gestures
}

char* rtc_get_time() {
    static char buffer[32];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    return buffer;
}
