/*
Nathanial Hendler
2021
github.com/equant
*/

// Load Wi-Fi library
#include <WiFi.h>
#include <Apple2Idiot.h>
#include "credentials.h"
#include "a2i_weather.h"
#include "a2i_iss.h"
#include "a2i_chess.h"

#define AUTO_CONNECT_TO_WIFI 1
#define AUTO_CONNECT_TIMEOUT 5

Apple2Idiot a2i = Apple2Idiot();

/*################################################
#      Applications we're going to support       #
#
# An Apple ][ running this card may want to run
# several different "apps" that utilize the card.
# These "apps" are classes (instantiated below)
# which the main loop uses to handle/manage
# communication with the Apple.  For example, the
# card may want to handle requests to support
# programs on the Apple ][ such as a wifi
# selector, a chess game, and a weather lookup
# app.
################################################*/

Chess chess_app = Chess();
Weather weather_app = Weather();
Iss iss_app = Iss();

#define N_APPS 3
byte app_ids[N_APPS] = {APP_ISS, APP_WEATHER, APP_CHESS};

/*******************/
/*   Variables     */
/*******************/

byte current_app_id;

const long mainLoopInterval = 100; // millis
//const long mainLoopInterval = 10000; // millis
unsigned long lastMainLoopTime = 0;
byte lastAppleCommand = 0;

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);

    a2i.init();
    //chess_app.init(&a2i, &http);
    //weather_app.init(&a2i, &http);

#ifdef AUTO_CONNECT_TO_WIFI
    Serial.println("");
    Serial.print("Starting wifi, connecting to: ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    byte wifi_loop_count = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(600);
        wifi_loop_count++;
        Serial.print(".");
        if (wifi_loop_count > AUTO_CONNECT_TIMEOUT) {
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected successfully");
        Serial.print("Got IP: ");
        Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
    } else {
        Serial.println("");
        Serial.println("WiFi connection failed.");
    }
#else
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    Serial.println("Wifi autoconnect not enabled.  No wifi connection attempted.");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
#endif
    
    Serial.println("Setup done");
    current_app_id = app_ids[0];

}

/*################################################
#                      Main                      #
################################################*/

void loop() {

    if ((millis() - lastMainLoopTime) > mainLoopInterval) {
        //Serial.print(".");
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
            for (int i=0; i<N_APPS; i++) {
                Serial.print("App loop: ");
                Serial.println(i);
                Serial.print("Checking ID: ");
                Serial.println(app_ids[i]);
                if (command_byte == app_ids[i]) {
                    // We were sent an app id.
                    Serial.println("We were sent an app id");
                    if (current_app_id != command_byte) {
                        // We are talking to a new app
                        Serial.println("We are talking to a new app");
                        a2i.write_data(ESP_COMMAND_ADDRESS, ACK);
                        current_app_id = command_byte;
                    }
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
                    lastMainLoopTime = millis();
                    Serial.println("About to return");
                    return;
                }
            }
           
            /* If we got here, we need to pass the command to app's class to be handled */ 

            if (current_app_id == weather_app.appId) {
                Serial.println("Received a command for Weather()");
                weather_app.handleCommand(command_byte);
                Serial.println("...command for Weather() handled");
                a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                //a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
            }
            else if (current_app_id == iss_app.appId) {
                Serial.println("Received a command for ISS()");
                iss_app.handleCommand(command_byte);
                Serial.println("...command for ISS() handled");
                a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                //a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
            }
            else if (current_app_id == chess_app.appId) {
                Serial.println("Received a command for Chess()");
                chess_app.handleCommand(command_byte);
                Serial.println("...command for Chess() handled");
                a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                //a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
            }
            else {
                Serial.println("Received a command for UNKNOWN()");
            }
        }
        lastMainLoopTime = millis();
    }
}
