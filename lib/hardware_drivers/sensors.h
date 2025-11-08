#ifndef SENSORS_H
#define SENSORS_H

void sensors_init();
int imu_read_gesture();
char* rtc_get_time();

#endif // SENSORS_H
