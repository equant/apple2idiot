# Arduno sketch for Apple2 Internet Weather Client Examples

For now, this works with both the basic and and cc65 clients

`../15_fixed_essid_weather-basic`
`../15_fixed_essid_weather-cc65`
if arduino-cli compile --fqbn esp32:esp32:nodemcu-32s .; then arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32-poe-iso .; fi
