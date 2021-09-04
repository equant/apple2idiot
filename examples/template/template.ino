/*

Use this program with the Apple2idIOT card and the basic programs RRAM, WRAM and CMDROT to read/write and rot13
a single string contained within the dual port ram on the card.

*/

// Load Wi-Fi library
#include <WiFi.h>
#include <Apple2Idiot.h>

Apple2Idiot a2i = Apple2Idiot();

void setup() {
    Serial.begin(115200);
    a2i.init();
}


void loop() {

}
