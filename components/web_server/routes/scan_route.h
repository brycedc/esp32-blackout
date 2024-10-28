#ifndef SCAN_ROUTE_H
#define SCAN_ROUTE_H

#include "esp_http_server.h"

/**
 * @brief Grabs the Scan API struct
 *
 * @return const httpd_uri_t*
 */
const httpd_uri_t *getScanRoute(void);

#endif