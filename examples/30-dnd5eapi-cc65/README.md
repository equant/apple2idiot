```bash
if arduino-cli compile --fqbn esp32:esp32:nodemcu-32s .; then arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32-poe-iso .; fi
```
