#ifdef DISABLED_FOR_NOW
#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include "esp_err.h"
#include <stdbool.h>
#include <stdint.h>
#include "host/ble_gap.h"


#define BLE_SCAN_DURATION_MS_DEFAULT 1000

typedef void (*ble_data_handler_t)(struct ble_gap_event *event, uint32_t event_data_len);

esp_err_t ble_manager_scan(uint32_t duration_ms);
esp_err_t ble_manager_scan_start(uint32_t duration_ms);
void ble_init(void);
esp_err_t ble_register_handler(ble_data_handler_t handler);
esp_err_t ble_unregister_handler(void);

#endif // BLE_MANAGER_H
#endif