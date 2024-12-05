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

/**
 * @brief Decomplied function that overrides original one at compilation time.
 *
 * @attention This function is not meant to be called!
 * @see Project with original idea/implementation
 * https://github.com/risinek/esp32-wifi-penetration-tool
 */
extern int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
  return 0;
}