# ESP32 Blackout

## Disclaimer

This project is intended for educational purposes only. The author assumes no responsibility for any misuse or damage that may result from the use of this software. By using this project, you acknowledge and agree to use it responsibly and in compliance with all applicable laws and regulations.

## Dependencies

This project utilizes the Espressif IoT Development Framework.

https://github.com/espressif/esp-idf

### Building the Project

```bash
idf.py build
```

### Flashing the Project

```bash
idf.py flash 
```

### Monitoring the Project

```bash
idf.py monitor
```

## Blackout AP Settings

To configure the SSID, password, and max connections of ESP32 access point run the following command.

```bash
idf.py menuconfig
```

A menu under the name of **Wifi Controller Settings** should appear. Under that menu you can change the SSID, password, and max connections