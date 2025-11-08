#ifndef SENSORS_H
#define SENSORS_H

// Initialize all sensors
void sensors_init();

// Read a gesture from the IMU
int imu_read_gesture();

// Get the time from the RTC
char* rtc_get_time();

#endif // SENSORS_H
