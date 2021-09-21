# apple2idiot
A general purpose ESP32 IOT board for the Apple IIe

The best example at the moment is `weather/`.

## Potential requirements

Some of these examples require things.  Here are some notes I've been taking...

### Arduino Libraries

+ https://github.com/me-no-dev/ESPAsyncWebServer
+ https://github.com/me-no-dev/AsyncTCP
+ ArduinoJSON by Benoit Blanchon

Instructions for installing Arduino libraries: https://www.arduino.cc/en/Guide/Libraries

Download the zips from github...

```bash
cd ~/Arduino/libraries
unzip AsyncTCP-master.zip
unzip ESPAsyncWebServer-master.zip
mv AsyncTCP-master AsyncTCP
mv ESPAsyncWebServer-master ESPAsyncWebServer
```

For ESP32 webserver to serve static files...

+ https://github.com/me-no-dev/arduino-esp32fs-plugin
