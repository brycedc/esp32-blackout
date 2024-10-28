#include "web_server.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "routes/scan_route.h"

static const char *TAG = "web_server";

/* Web Server Configuration */
#define ESP_WEB_SERVER_PORT CONFIG_WEB_SERVER_PORT

void webctl_start_server(void) {
  // Generate default configuration
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  // Empty handle to esp_http_server
  httpd_handle_t server = NULL;

  // Start the httpd server
  if (httpd_start(&server, &config) == ESP_OK) {
    // Registers endpoint handlers
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, getScanRoute()));
    ESP_LOGI(TAG, "Successfully started web server on port:%d",
             ESP_WEB_SERVER_PORT);
  }

  // If server failed to start, server will be NULL
  // Prints a log if the server failed
  if (server == NULL) {
    ESP_LOGE(TAG, "Failed to start web server...");
    abort();
  }
}