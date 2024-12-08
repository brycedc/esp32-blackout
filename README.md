# ESP32 Blackout

## ⚠️ Disclaimer

This project is intended for educational purposes only. The author assumes no responsibility for any misuse or damage that may result from the use of this software. By using this project, you acknowledge and agree to use it responsibly and in compliance with all applicable laws and regulations.

## Dependencies

This project utilizes the Espressif IoT Development Framework.

https://github.com/espressif/esp-idf

> [!IMPORTANT]
> I have been using **v5.3.1** for building and flashing this project.

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

## ☁️ API Endpoints

The ESP32 endpoints can be hit to gather information or attack a network. The default host will be **192.168.4.1**

### `/api/scan`

Method: GET

This endpoint performs a network scan and returns all the access points nearby with the following information.

- SSID: the name of the access point
- BSSID: the mac address of the access point
- RSSI: the power of the access point (how close it is)
- Channel: the channel the access point is operating on

### `/api/deauth`

Method: POST

```json
{
  "bssid": "aa:bb:cc:dd:ee:ff",
  "channel": 1,
  "timeout": 30
}
```

This endpoint performs a deauth attack by spoofing a management deauth frame and sending it once every second on the provided channel.

- BSSID: the mac address of the access point to spoof
- Channel: the channel to broadcast from (this needs to match the channel of the access point you are trying to spoof)
- Timeout: the number of seconds to broadcast for. A spoofed frame is sent every second.
