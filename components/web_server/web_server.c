#include "web_server.h"
#include "esp_log.h"
#include "esp_http_server.h"

static const char *TAG = "web_server";

/* Web Server Configuration */
#define ESP_WEB_SERVER_PORT CONFIG_WEB_SERVER_PORT

httpd_handle_t webctl_start_server(void) {
  // Generate default configuration
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  // Empty handle to esp_http_server
  httpd_handle_t server = NULL;

  // Start the httpd server
  if (httpd_start(&server, &config) == ESP_OK) {
    ESP_LOGI(TAG, "Successfully started web server on port:%d", ESP_WEB_SERVER_PORT);
    /*
      Register URI handlers here
    */
  }

  // If server failed to start, handle will be NULL
  // Prints a log if the server failed
  if (server == NULL) {
    ESP_LOGE(TAG, "Failed to start web server...");
  } 

  return server;
}