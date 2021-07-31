# apple2idiot
A general purpose ESP32 IOT board for the Apple IIe

# Requirements

## Arduino Libraries

+ https://github.com/me-no-dev/ESPAsyncWebServer
+ https://github.com/me-no-dev/AsyncTCP

Instructions for installing Arduino libraries: https://www.arduino.cc/en/Guide/Libraries

Download the zips from github...

```bash
cd ~/Arduino/libraries
unzip AsyncTCP-master.zip
unzip ESPAsyncWebServer-master.zip
mv AsyncTCP-master AsyncTCP
mv ESPAsyncWebServer-master ESPAsyncWebServer
```

## Potential requirements

For ESP32 webserver to serve static files...

+ https://github.com/me-no-dev/arduino-esp32fs-plugin
