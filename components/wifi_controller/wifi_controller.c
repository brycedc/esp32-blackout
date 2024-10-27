#include "wifi_controller.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_wifi_default.h"

static bool wifi_init = false;
static const char *TAG = "wifi_controller";

/* Blackout Configuration */
#define ESP_WIFI_AP_SSID CONFIG_AP_SSID
#define ESP_WIFI_AP_PASSWD CONFIG_AP_PASSWD
#define ESP_WIFI_MAX_STA_CONN CONFIG_MAX_CONN

void wifictl_init(void) {

  // This function should only be called once
  if (wifi_init) {
    ESP_LOGW(TAG, "wifictl_init should only be called once");
    return;
  }

  // Initialize the underlying TCP/IP stack
  ESP_ERROR_CHECK(esp_netif_init());

  // Sets up a default ap (provides DHCP event task)
  esp_netif_create_default_wifi_ap();

  // Initializes WIFI with default configuration
  wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&config));

  wifi_init = true;
}

void wifictl_ap_start(wifi_config_t *wifi_config) {

  // Checks that the WIFI init function was called
  if (!wifi_init) {
    wifictl_init();
  }

  // Sets the WIFI operating mode to AP
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
  ESP_LOGI(TAG, "set wifi mode to AP");

  // Sets the AP configuration
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, wifi_config));

  // Starts the wifi
  ESP_ERROR_CHECK(esp_wifi_start());
  ESP_LOGI(TAG, "AP started. SSID:%s password:%s channel:%d",
           wifi_config->ap.ssid, wifi_config->ap.password,
           wifi_config->ap.channel);
}

void wifictl_start_blackout(void) {

  wifi_config_t wifi_config = {
      .ap =
          {
              .ssid = ESP_WIFI_AP_SSID,
              .ssid_len = sizeof(ESP_WIFI_AP_SSID),
              .password = ESP_WIFI_AP_PASSWD,
              .max_connection = ESP_WIFI_MAX_STA_CONN,
              .authmode = WIFI_AUTH_WPA2_PSK,
          },
  };

  wifictl_ap_start(&wifi_config);
}