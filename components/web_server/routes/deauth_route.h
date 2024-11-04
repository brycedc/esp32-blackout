#ifndef DEAUTH_ROUTE_H
#define DEAUTH_ROUTE_H

#include "esp_http_server.h"

/**
 * @brief Grabs the Scan API struct
 *
 * @return const httpd_uri_t*
 */
const httpd_uri_t *getDeAuthRoute(void);

#endif