#include "deauth_route.h"
#include "cJSON.h"
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "wifi_controller.h"
#include <stdio.h>
#include <string.h>

#define BSSID_LENGTH 6

static const char *TAG = "routes/deauth";

esp_err_t ascii_to_bssid(const char *ascii_bssid,
                         uint8_t bssid_out[BSSID_LENGTH]) {
  // Checks for NULL input
  if (ascii_bssid == NULL || bssid_out == NULL) {
    return ESP_ERR_INVALID_ARG;
  }

  // Use sscanf to parse the BSSID address
  int ret = sscanf(ascii_bssid, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &bssid_out[0],
                   &bssid_out[1], &bssid_out[2], &bssid_out[3], &bssid_out[4],
                   &bssid_out[5]);

  if (ret != BSSID_LENGTH) {
    return ESP_ERR_INVALID_ARG;
  }

  return ESP_OK;
}

static esp_err_t route_handler(httpd_req_t *req) {
  // Read the data from the request
  char buf[100];

  // Grabs request from user
  httpd_req_recv(req, buf, sizeof(buf));

  // Parse the JSON
  cJSON *json = cJSON_Parse(buf);
  if (json == NULL) {
    ESP_LOGE(TAG, "Invalid JSON format");
    ESP_ERROR_CHECK(httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON format"));
    return ESP_FAIL;
  }

  // Extract the BSSID and the radio channel
  cJSON *bssid = cJSON_GetObjectItem(json, "bssid");
  if (bssid == NULL) {
    ESP_LOGE(TAG, "Failed to get BSSID from JSON object");
    cJSON_Delete(json);
    ESP_ERROR_CHECK(httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST,
                        "Json object was missing a bssid tag"));
    return ESP_FAIL;
  }

  cJSON *channel = cJSON_GetObjectItem(json, "channel");
  if (channel == NULL) {
    ESP_LOGE(TAG, "Failed to get BSSID from JSON object");
    cJSON_Delete(json);
    ESP_ERROR_CHECK(httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST,
                        "Json object was missing a bssid tag"));
    return ESP_FAIL;
  }

  uint8_t bssid_bytes[BSSID_LENGTH];
  esp_err_t err = ascii_to_bssid(bssid->valuestring, bssid_bytes);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to convert BSSID to bytes");
    cJSON_Delete(json);
    ESP_ERROR_CHECK(httpd_resp_send_500(req));
    return ESP_FAIL;
  }

  // Starts deauth attack
  wifictl_deauth(bssid_bytes, channel->valueint);

  // Sends status 200 code back
  ESP_ERROR_CHECK(httpd_resp_send(req, NULL, 0));
  return ESP_OK;
}

static httpd_uri_t deauth_route = {
    .uri = "/api/deauth",
    .method = HTTP_POST,
    .handler = route_handler,
    .user_ctx = NULL,
};

const httpd_uri_t *getDeAuthRoute(void) { return &deauth_route; }