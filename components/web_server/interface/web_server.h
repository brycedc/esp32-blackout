#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "esp_http_server.h"

/**
 * @brief Starts the web server
 *
 * @return Returns a httpd_handle_t, if the handle is NULL an error was
 * encountered
 */
httpd_handle_t webctl_start_server(void);

#endif