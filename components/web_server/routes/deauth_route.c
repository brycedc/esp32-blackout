#include "deauth_route.h"
#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "wifi_controller.h"

static const char *TAG = "routes/deauth";

static esp_err_t route_handler(httpd_req_t *req) {
  // Read the data from the request
  char buf[50];
  httpd_req_recv(req, buf, sizeof(buf));

  // Starts deauth attack
  wifictl_deauth((uint8_t *)buf);

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