# apple2idiot

A general purpose ESP32 IOT board for the Apple IIe

Things are in the early stages of development, but it is working.  The card contains an ESP32 which gives the Apple II access to wifi and bluetooth.  It does not provide a TCP stack.  Think of this as being more like making your Apple II an IOT device.

## Status

### The Card

This is actively being developed (as of September 2021).  The rev 0.2 board doesn't work without
some bodge wires

Rev 0.2 boards are going to be ordered sometime this month.

### The Apple II Software

None of the Apple //e code is up yet because I don't have a way to transfer it
from my 5.25 floppies to here.  But all of this is underway.

### The Card Software

The ESP32 can be programmed using whatever you want.  For example, you can use the Arduino IDE/C++ or you can use Lua, or Espressif's environment.  Example Arduino programs are in the repo under examples.

## Some of the example programs that have been developed so far

* Get current weather conditions for a city.
* Select Wifi AP.
* Dedicated rot13 string encoder.

## What could be done with an Apple2Idiot card?

Here are some things I'm interested in making work...

* Prodos clock driver (NTP -> ESP -> Prodos)
* Home automation using MQTT
* Peer-to-peer local area chat/games using ESPNOW or something similar
* Wikipedia access

## Want to help?

There are lots of jobs both little and big and hard and easy for someone
looking for a project to join.  Take a look at the list above for ideas.  Feel
free to email me at nathanhendler@gmail.com.

