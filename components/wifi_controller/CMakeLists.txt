idf_component_register(SRCS 
                      "wifi_controller.c" 
                      "attacks/scanner.c" 
                      "attacks/deauth.c"
                    INCLUDE_DIRS "interface"
                    REQUIRES esp_wifi)

# This is needed to bypass subtype lock by ESP32 to send deauth frames
target_link_libraries(${COMPONENT_LIB} -Wl,-zmuldefs)