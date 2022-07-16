
# Overview

This is a very simple example of how to scan for wifi access points and then
connect to one.  It is a very basic example of how the Apple2Idiot card and the
Apple II can work together.  Practically, this example isn't very useful,
because after you connect you can not really do anything except recscan.
There's no code in `01_wifi_scan-basic.ino` to do anything else.  

## Getting it to work

#. Load `01_wifi_scan-basic.dsk` into your Apple II
#. Load `01_wifi_scan-basic.ino` into your apple2idiot card in slot 2.

At BASIC prompt on Apple II do...

```BASIC
RUN CWIFISCAN.BAS
RUN WIFISCAN.BAS
RUN SHOWIP.BAS
```

CWIFISCAN tells the card to scan for access points.

WIFISCAN shows the results, and lets you choose an access point and enter a password

SHOWIP does just that.

## Building the .dsk image

```bash
. ./make-disk.bash
```

## Flashing card using arduino-cli

You can use the arduino ide to get the .ino file onto the Apple2Idiot card.  Or you can use the `arduino-cli` which is explained here...

```bash
arduino-cli compile --fqbn esp32:esp32:nodemcu-32s .
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32-poe-iso .
```

