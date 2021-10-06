/*
Use this program with the Apple2idIOT card and the basic programs RRAM, WRAM and CMDROT to read/write and rot13
a single string contained within the dual port ram on the card.
CA = 49664
AA = CA + 1
*/

// Load Wi-Fi library
#include <WiFi.h>
#include <Apple2Idiot.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "credentials.h"
#include "a2i_chess.h"

//const char* wifi_ssid = WIFI_SSID;
//const char* wifi_password = WIFI_PASSWORD;

/*################################################
#      Applications we're going to support       #
################################################*/

Apple2Idiot a2i = Apple2Idiot();
HTTPClient http;
Chess chess_app = Chess();

#define N_APPS 1
byte app_ids[N_APPS] = {APP_CHESS};

/*******************/
/*   Variables     */
/*******************/

byte current_app_id;

//const long mainLoopInterval = 100; // millis
const long mainLoopInterval = 10000; // millis
unsigned long lastMainLoopTime = 0;
byte lastAppleCommand = 0;

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);

    a2i.init();
    chess_app.init(&a2i, &http);


    Serial.println("");
    Serial.println("Starting wifi...");
    Serial.print("  connecting to: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(600);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
    
    Serial.println("Setup done");
    current_app_id = app_ids[0];

    //chess_app.validateMove("g8f6");
    //chess_app.makeMove("g8f6");
    //chess_app.getBoard();
}

/*################################################
#                      Main                      #
################################################*/

void loop() {

    if ((millis() - lastMainLoopTime) > mainLoopInterval) {
        byte command_byte = a2i.read_data(APPLE_COMMAND_ADDRESS);
        if (command_byte == RAM_BUSY) {
            Serial.println("Command Read: RAM BUSY");
        }
        else if (command_byte != lastAppleCommand){
            lastAppleCommand = command_byte;
            byte result = 0;
            Serial.print("Handling command_byte: ");
            Serial.println(command_byte);

            /* Do we need to switch app context? */

            for (int i; i<N_APPS; i++) {
                if (command_byte == app_ids[i]) {
                    // We were sent an app id.
                    Serial.println("We were sent an app id");
                    if (current_app_id != command_byte) {
                        // We are talking to a new app
                        Serial.println("We are talking to a new app");
                        a2i.write_data(ESP_COMMAND_ADDRESS, ACK);
                        current_app_id = command_byte;
                        a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                        a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
                        lastMainLoopTime = millis();
                        return;
                    }
                }
            }
           
            /* If we got here, we need to pass the command to app's class to be handled */ 

            if (command_byte == chess_app.appId) {
                Serial.println("Received a command for Chess()");
                chess_app.handleCommand(command_byte);
                a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                //a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
            }
        }
        lastMainLoopTime = millis();
    }
}
