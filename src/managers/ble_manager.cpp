#ifdef DISABLED_FOR_NOW
#include "managers/ble_manager.h"
#include "esp_nimble_hci.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include <esp_log.h>
#include "host/ble_gap.h"


#define TAG "BLEManager"

static ble_data_handler_t s_ble_data_handler = NULL;

static int ble_gap_event(struct ble_gap_event *event, void *arg) {
  switch (event->type) {
  case BLE_GAP_EVENT_DISC:
    if (s_ble_data_handler != NULL) {
      s_ble_data_handler(event, 0);
    }
    return 0;
  }
  return 0;
}

static void ble_scan_task(void *param) {
  ble_manager_scan(BLE_SCAN_DURATION_MS_DEFAULT);
  vTaskDelete(NULL);
}

esp_err_t ble_manager_scan_start(uint32_t duration_ms) {
  xTaskCreate(ble_scan_task, "ble_scan_task", 4096, NULL, 5, NULL);
  return ESP_OK;
}

esp_err_t ble_register_handler(ble_data_handler_t handler) {
  s_ble_data_handler = handler;
  return ESP_OK;
}

esp_err_t ble_unregister_handler(void) {
  s_ble_data_handler = NULL;
  return ESP_OK;
}

void ble_on_sync(void) {
  ble_manager_scan_start(BLE_SCAN_DURATION_MS_DEFAULT);
}

void ble_host_task(void *param) { nimble_port_run(); }

void ble_init(void) {
  ESP_ERROR_CHECK(esp_nimble_hci_and_controller_init());
  nimble_port_init();

  ble_svc_gap_device_name_set("GHOST-ESP32");
  ble_svc_gap_init();
  ble_svc_gatt_init();
  ble_hs_cfg.sync_cb = ble_on_sync;

  nimble_port_freertos_init(ble_host_task);
}

esp_err_t ble_manager_scan(uint32_t duration_ms) {
  struct ble_gap_disc_params disc_params;
  disc_params.filter_duplicates = 1;
  disc_params.passive = 1;
  disc_params.itvl = 0;
  disc_params.window = 0;
  disc_params.filter_policy = 0;
  disc_params.limited = 0;

  int rc =
      ble_gap_disc(BLE_OWN_ADDR_PUBLIC, duration_ms, &disc_params,
                   ble_gap_event, NULL);
  if (rc != 0) {
    ESP_LOGE(TAG, "Error starting BLE scan: %d", rc);
    return ESP_FAIL;
  }

  return ESP_OK;
}
#endif