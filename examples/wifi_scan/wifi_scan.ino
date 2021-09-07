/*
Use this program with the Apple2idIOT card and the basic programs RRAM, WRAM and CMDROT to read/write and rot13
a single string contained within the dual port ram on the card.
*/

#include <WiFi.h>
#include <Apple2Idiot.h>

Apple2Idiot a2i = Apple2Idiot();

const char* wifi_ssid = "";
const char* wifi_password = "";

const long readLoopInterval = 100; // millis
unsigned long lastReadLoopTime = 0;

byte lastAppleCommand = 0;

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);
    a2i.init();

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    Serial.println("Setup done");
}

/*################################################
#                      Main                      #
################################################*/

void scan_wifi() {
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    int address_counter = SHARED_RAM_START_ADDRESS + 1;
    if (n == 0) {
        Serial.println("no networks found");
        a2i.write_data(0, address_counter);
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        a2i.write_data(n, address_counter);
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.println(WiFi.SSID(i));
            delay(10);
            address_counter = a2i.write_string_to_shared_ram(WiFi.SSID(i), address_counter + 1);
        }
    }
    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
    Serial.println("");
}

void store_ip_to_ram(byte offset) {
    IPAddress ip_address = WiFi.localIP();
    for (int i=0; i < 4; i++) {
        a2i.write_data(i+offset, ip_address[i]);
    }
}

void loop() {

    if ((millis() - lastReadLoopTime) > readLoopInterval) {
        byte command_byte = a2i.read_data(APPLE_COMMAND_ADDRESS);
        if (command_byte == RAM_BUSY) {
            Serial.println("Command Read: RAM BUSY");
        }
        else if (command_byte != lastAppleCommand){
            Serial.print("Command Switch command_byte: ");
            Serial.println(command_byte);
            switch(command_byte) {
                case COMMAND_SCAN_WIFI:
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    scan_wifi();
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    break;
            }
            switch(command_byte) {
                case COMMAND_CONNECT:
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    int access_point_n = a2i.read_data(SHARED_RAM_START_ADDRESS) - 1;
                    String ssid_as_String = WiFi.SSID(access_point_n);
                    String password_as_String = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS+1);
                    wifi_password = password_as_String.c_str();
                    wifi_ssid = ssid_as_String.c_str();
                    if (wifi_password == "xerxes27") {
                        Serial.println("PASSWORDS ARE NOT THE SAME!");
                    } else {
                        Serial.println("Passwords are the same...");
                        Serial.print("PASS:["); Serial.print(wifi_password); Serial.println("]");
                    }
                    Serial.print("SSID_from_n:[");Serial.print(wifi_ssid);Serial.println("]");
                    WiFi.begin(wifi_ssid, wifi_password);
                    while (WiFi.status() != WL_CONNECTED) {
                        delay(300);
                        Serial.print(".");
                    }
                    Serial.println("");
                    Serial.println("WiFi connected successfully");
                    Serial.print("Got IP: ");
                    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
                    store_ip_to_ram(SHARED_RAM_START_ADDRESS);
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    break;
            }
            lastAppleCommand = command_byte;
            a2i.write_data(ESP_COMMAND_ADDRESS, EOT);      // notify Apple IIe we are done processing command byte
        }
        lastReadLoopTime = millis();
    }
}
