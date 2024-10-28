#include "scan_route.h"
#include "cJSON.h"
#include "esp_http_server.h"
#include "wifi_controller.h"

static esp_err_t route_handler(httpd_req_t *req) {
  // Starts scanning for access points
  wifictl_scan();

  // Grabs the list of access points found
  const wifictl_ap_records_t *ap_records = wifictl_get_records();

  // Sets the HTTP content type
  httpd_resp_set_type(req, HTTPD_TYPE_JSON);

  // Creates JSON object
  cJSON *json_array = cJSON_CreateArray();

  // Loops through the list and builds a response message
  for (int i = 0; i < ap_records->num_records; i++) {
    // Grabs the instance of the record
    const wifi_ap_record_t *curr_record = &ap_records->records[i];

    // Creates a json record
    cJSON *json_record = cJSON_CreateObject();
    cJSON_AddStringToObject(json_record, "SSID",
                            (const char *)curr_record->ssid);
    // Creates the BSSID string
    char bssid_str[18]; // MAC address in format XX:XX:XX:XX:XX:XX
    sprintf(bssid_str, "%02x:%02x:%02x:%02x:%02x:%02x", curr_record->bssid[0],
            curr_record->bssid[1], curr_record->bssid[2], curr_record->bssid[3],
            curr_record->bssid[4], curr_record->bssid[5]);
    cJSON_AddStringToObject(json_record, "BSSID", bssid_str);
    cJSON_AddNumberToObject(json_record, "RSSI", curr_record->rssi);
    cJSON_AddNumberToObject(json_record, "Channel", curr_record->primary);

    // Add to json array
    cJSON_AddItemToArray(json_array, json_record);
  }

  // Sends the response
  char *json_string = cJSON_Print(json_array);
  httpd_resp_send(req, json_string, strlen(json_string));

  // Cleanup
  cJSON_Delete(json_array);

  return ESP_OK;
}

static httpd_uri_t scan_route = {
    .uri = "/api/scan",
    .method = HTTP_GET,
    .handler = route_handler,
    .user_ctx = NULL,
};

const httpd_uri_t *getScanRoute(void) { return &scan_route; }
