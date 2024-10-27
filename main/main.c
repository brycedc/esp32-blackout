/**
 * @file main.c
 * @author brycedc 
 * @date 2024-10-26
 * @copyright Copyright (c) 2024
 *
 * @brief Main File used to setup ESP32
 *
 * Starts the access AP
 */

#include "esp_event.h"
#include "nvs_flash.h"
#include "wifi_controller.h"
#include "web_server.h"

static const char *TAG = "main";

void app_main(void) {
  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // Initialize default event loop
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  // Starts the blackout AP
  wifictl_start_blackout();

  // Starts web server
  webctl_start_server();
}
