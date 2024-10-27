#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include "esp_wifi_types_generic.h"

/**
 * @brief Starts an access point
 * 
 * @param wifi_config config struct for the AP
 */
void wifictl_ap_start(wifi_config_t *wifi_config); 

/**
 * @brief Starts the Blackout Access Point
 * 
 */
void wifictl_start_blackout(void); 

#endif