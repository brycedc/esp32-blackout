#ifndef WEB_SERVER_H
#define WEB_SERVER_H

/**
 * @brief Starts the web server
 *
 * @return Returns a httpd_handle_t, if the handle is NULL an error was
 * encountered
 */
void webctl_start_server(void);

#endif