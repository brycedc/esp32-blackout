#ifndef SCANNER_H
#define SCANNER_H

#include "esp_wifi_types_generic.h"

/**
 * @brief List to store AP records after a scan
 * 
 */
typedef struct {
  uint16_t num_records;
  wifi_ap_record_t records[CONFIG_SCAN_MAX_AP];
} wifictl_ap_records_t;

/**
 * @brief Scans for nearby access points
 * 
 * @note Calling this will clear the previous records
 */
void wifictl_scan(void);

/**
 * @brief Returns the list of ap records found after a scan
 * 
 * @return const wifi_ap_record_t* 
 */
const wifictl_ap_records_t *wifictl_get_records(void);

#endif