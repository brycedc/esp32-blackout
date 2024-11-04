idf_component_register(SRCS "web_server.c" "routes/scan_route.c" "routes/deauth_route.c" 
                    INCLUDE_DIRS "interface"
                    PRIV_REQUIRES esp_http_server wifi_controller json)
