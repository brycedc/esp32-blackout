idf_component_register(SRCS "main.c"  
                    INCLUDE_DIRS .)

# This is needed to bypass subtype lock by ESP32 to send deauth frames
target_link_libraries(${COMPONENT_LIB} -Wl,-zmuldefs)