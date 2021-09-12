# apple2idiot

A general purpose ESP32 Wifi and Bluetooth board for the Apple II family of computers (with expansion slots).  

This card is essentially an ESP32 module and a dual-port ram chip.  The Apple computer and the ESP communicate via the dual-port ram.  That means that the ESP32 doesn't acutally have access to read/write any of the Apple computer's data or address busses.  I think that's ok.  In fact, I think this card is so simple, and stupid, that lots of fun little things can be done with it, but it's not meant to "get your Apple on the internet".

As a user of the card, you write the software that runs on the ESP32 module, and the software that runs on the Apple computer.  In the `examples/` folder are examples of how to do simple little things.  Software on the apple just peeks/pokes commands and data to the ram chip, and the ESP responds however it's programmed to resppond.

## Some of the example programs that have been developed so far

* Send a message to Slack.
* Get current weather conditions for a city.
* Select Wifi AP.
* Dedicated rot13 string encoder.

## Status

### The Card

This is actively being developed (as of September 2021).  The rev 0.1 board doesn't work without
some bodge wires, and rev 0.2 boards are on their way from China.

### The Apple II Software

None of the Apple //e code is up yet because I don't have a way to transfer it
from my 5.25 floppies to here.  I hope to fix this soon.

### The Card Software/Firmware

The ESP32 can be programmed using whatever you want.  For example, you can use
the Arduino IDE/C++ or you can use Lua, or Espressif's environment.  Example
Arduino programs are in the repo under examples.

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

