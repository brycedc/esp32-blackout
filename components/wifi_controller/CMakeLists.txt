idf_component_register(SRCS 
                      "wifi_controller.c" 
                      "attacks/scanner.c" 
                      "attacks/deauth.c"
                    INCLUDE_DIRS "interface"
                    REQUIRES esp_wifi)
