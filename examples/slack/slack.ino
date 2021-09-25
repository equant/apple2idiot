/*
*/

// Load Wi-Fi library
//#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include <Apple2Idiot.h>
#include "ArduinoSlack.h"
#include "credentials.h"
#include "ArduinoSlackCert.h"
// copy credentials.h.sample to credentials.h and edit
// so it contains your passwords and tokens.

Apple2Idiot a2i = Apple2Idiot();

WiFiClientSecure client;
ArduinoSlack slack(client, SLACK_ACCESS_TOKEN);

#define COMMAND_SET_CHANNEL 200
#define COMMAND_SEND_MESSAGE 201
#define COMMAND_GET_CHANNEL_MESSAGES 202

char wifi_ssid[] = WIFI_SSID;         // your network SSID (name)
char wifi_password[] = WIFI_PASSWORD; // your network password

/*******************/
/*    Misc         */
/*******************/
SlackUsersConversations conversation;

//const long readLoopInterval = 100; // millis
const long readLoopInterval = 44000; // millis
unsigned long lastReadLoopTime = 0;

byte lastAppleCommand = 0;

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);

    a2i.init();

    Serial.println("");
    Serial.println("Starting wifi...");
    Serial.print("  connecting to: ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(600);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
    client.setCACert(slack_server_cert);
    
    //Serial.println(conversation);

    int slack_attempts=1;
    do {
        yield();
        conversation = slack.usersConversations();
    } while (conversation.error && ++slack_attempts < 5);

    yield();
    Serial.println("+-+-+-+- CHANNELS -+-+-+-+-+-+-+-+:");
    //for (int i=0; i< sizeof(conversation.channelNames)-5; i++) {
    //for (int i=0; i<5; i++) {
        //Serial.print(conversation.channelNames[i]);
        //Serial.print(" -> ");
        //Serial.println(conversation.channelIds[i]);
    //}
    yield();
    Serial.println(conversation.channelNames[0]);
    Serial.println(conversation.channelNames[1]);
    Serial.println(conversation.channelNames[2]);
    Serial.println(conversation.channelNames[-1]);

    Serial.println("Setup done");
}

/*################################################
#                   Functions                    #
################################################*/


/*################################################
#                      Main                      #
################################################*/

//String channel_name = "equant-test";
String channel_name = "C02EAQECY5A";
String message = "";

void loop() {

    if ((millis() - lastReadLoopTime) > readLoopInterval) {


        byte command_byte = a2i.read_data(APPLE_COMMAND_ADDRESS);
        if (command_byte == RAM_BUSY) {
            Serial.println("Command Read: RAM BUSY");
        }
        else if (command_byte != lastAppleCommand){
            byte result = 0;
            Serial.print("Command Switch command_byte: ");
            Serial.println(command_byte);
            switch(command_byte) {
                case COMMAND_GET_CHANNEL_MESSAGES:
                    Serial.println("COMMAND_GET_CHANNEL_MESSAGES");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    char cc[250];
                    channel_name.toCharArray(cc, 250);
                    conversation = slack.usersConversations();
                    //serializeJsonPretty(conversation.messageObj, Serial);
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
                    break;
                case COMMAND_SET_CHANNEL:
                    Serial.println("COMMAND_SET_CHANNEL");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    channel_name = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    Serial.println("Received: ["+channel_name+"]");
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
                    break;
                case COMMAND_SEND_MESSAGE:
                    Serial.println("COMMAND_SEND_MESSAGE:");
                    SlackMessage slackMessage;
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    message = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    char m[250];
                    message.toCharArray(m, 250);
                    char c[250];
                    channel_name.toCharArray(c, 250);
                    slackMessage = slack.postMessage(c, m);
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, result);   // notify Apple IIe we are done processing command byte
                    break;
            }
            lastAppleCommand = command_byte;
        }
        lastReadLoopTime = millis();
    }
}
