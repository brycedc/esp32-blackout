#ifndef DEAUTH_H
#define DEAUTH_H

#include <stdint.h>

/**
 * @brief Broadcasts a deauth frame from the target bssid
 * 
 * @param target_bssid The BSSID of the target access point
 */
void wifictl_deauth(const uint8_t target_bssid[6], const int channel);

#endif