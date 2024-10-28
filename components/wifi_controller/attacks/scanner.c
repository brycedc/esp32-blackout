#include "scanner.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "sdkconfig.h"

static const char *TAG = "wifi_controller/scanner";

// Stores last AP scan results
static wifictl_ap_records_t ap_records;

void wifictl_scan(void) {
  ESP_LOGI(TAG, "Scanning nearby APs...");

  // Creates a scan configuration
  const wifi_scan_config_t scan_config = {
    .ssid = NULL,
    .bssid = NULL,
    .channel = 0,
    .scan_type = WIFI_SCAN_TYPE_ACTIVE
  };

  // Default access points scan
  ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

  // Clears the num_records on the ap_records
  ap_records.num_records = CONFIG_SCAN_MAX_AP;

  // Grabs the list of access points found
  esp_wifi_scan_get_ap_records(&ap_records.num_records, ap_records.records);
  ESP_LOGI(TAG, "Discovered %u APs", ap_records.num_records);
}

const wifictl_ap_records_t *wifictl_get_records(void) {
  return &ap_records;
}