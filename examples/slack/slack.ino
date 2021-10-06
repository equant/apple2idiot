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

char wifi_ssid[] = WIFI_SSID;         // your network SSID (name)
char wifi_password[] = WIFI_PASSWORD; // your network password

/*******************/
/*    Misc         */
/*******************/
SlackUsersConversations conversation;

//const long readLoopInterval = 100; // millis
const long readLoopInterval = 11000; // millis
unsigned long lastReadLoopTime = 0;

byte lastAppleCommand = 0;

//String channel_name = "equant-test";
//C02EAQECY5A

const char current_channel_name = 'equant-test';
const char current_channel_id   = 'C02EAQECY5A';

String current_channel_str = "";
String message = "";
int current_channel_n = -1;

/*################################################
#                   Functions                    #
################################################*/

int find_channel_number(String channel_str_from_apple) {
    Serial.println("find_channel_number()");
    for (int i=0; i< conversation.n_channels; i++) {
        if (channel_str_from_apple == String(conversation.channelNames[i])) {
            Serial.print("    Found:"); Serial.println(conversation.channelNames[i]);
            return i;
        }
        if (channel_str_from_apple == String(conversation.channelIds[i])) {
            Serial.print("    Found:"); Serial.println(conversation.channelIds[i]);
            return i;
        }
    }
    Serial.println("    No channel found:");
    return -1;
}


void get_slack_channels() {
    Serial.println("get_slack_channels()");
    int slack_attempts=1;
    do {
        yield();
        conversation = slack.usersConversations();
    } while (conversation.error && ++slack_attempts < 5);

    if (slack_attempts == 5) {
        Serial.println("    ERROR: Unable to negotiate usersConversations with Slack API");
    } else {
        Serial.println("+-+-+-+- CHANNELS -+-+-+-+-+-+-+-+:");
        for (int i=0; i< conversation.n_channels; i++) {
            Serial.print(conversation.channelNames[i]);
            Serial.print(" -> ");
            Serial.println(conversation.channelIds[i]);
        }
    }
}


SlackMessages channelMessages;

void get_channel_messages() {
    Serial.println();
    Serial.print("get_channel_messages() for channel: ");
    Serial.println(current_channel_id);
    int slack_attempts=1;
    int error=1;
    do {
        yield();
        error = slack.channelHistory(current_channel_id, &channelMessages);
    } while (channelMessages.error && ++slack_attempts < 5);

    if (slack_attempts == 5) {
        Serial.println("ERROR: Unable to negotiate usersConversations with Slack API");
    }
}



void send_channel_info(int channel_n) {
    Serial.println("send_channel_info()");
    int ac = 0;
    ac = a2i.write_data(SHARED_RAM_START_ADDRESS, current_channel_n);
    ac = a2i.write_string_to_shared_ram(String(conversation.channelNames[current_channel_n]), ac + 1);
    ac = a2i.write_string_to_shared_ram(String(conversation.purpose[current_channel_n]), ac + 1);
    ac = a2i.write_string_to_shared_ram(String(conversation.topic[current_channel_n]), ac + 1);
    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
}


void send_message_to_channel(String message) {
    Serial.println("send_message_to_channel()");
    Serial.print("    current_channel_n: "); Serial.println(current_channel_n);
    SlackMessage slackMessage;
    char m[250];
    message.toCharArray(m, 250);
    //char c[250];
    //channel_name.toCharArray(c, 250);
    slackMessage = slack.postMessage(conversation.channelIds[current_channel_n], m);
    Serial.print("    current_channel_n: "); Serial.println(current_channel_n);
    Serial.print("    message sent to channel: "); Serial.println(conversation.channelIds[current_channel_n]);
    find_channel_number("equant-test");
}


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
    
    //get_slack_channels();
    //current_channel_n = find_channel_number("equant-test");
    //yield();

    //Serial.println("");
    //send_message_to_channel("Insufficient facts always invite danger."); 

    //slack.channelHistory(conversation.channelIds[current_channel_n]); 
    get_channel_messages();

    Serial.println("Setup done");
}

/*################################################
#                      Main                      #
################################################*/


void showthing(char *thing) {
    Serial.println(thing);
    for (int j=0; j<strlen(thing)+2; j++) {
        Serial.print("["); Serial.print(thing[j]); Serial.print("]");
    }
    Serial.println();
}

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

                case COMMAND_GET_MESSAGES:
                    Serial.println("COMMAND_GET_CHANNEL_MESSAGES");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    //char cc[250];
                    //channel_name.toCharArray(cc, 250);
                    //conversation.channelIds[current_channel_n]; 
                    //conversation = slack.usersConversations();
                    //serializeJsonPretty(conversation.messageObj, Serial);
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
                    break;

                case COMMAND_SET_CHANNEL:
                    Serial.println("COMMAND_SET_CHANNEL");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    current_channel_str = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    current_channel_n = find_channel_number(current_channel_str);
                    if (current_channel_n < 0) {
                        a2i.write_data(ESP_COMMAND_ADDRESS, NOT_FOUND);
                        Serial.println("    Couldn't find requested channel.");
                    } else {
                        Serial.println("    Set channel to: ["+current_channel_str+"]");
                        send_channel_info(current_channel_n);
                        a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
                    }
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    break;

                case COMMAND_GET_CHANNEL_N:
                    Serial.println("COMMAND_GET_CHANNEL_N");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);
                    int requested_n;
                    requested_n = a2i.read_data(SHARED_RAM_START_ADDRESS);
                    send_channel_info(requested_n);
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
                    break;
                    
                case COMMAND_GET_CHANNEL_STR:
                    Serial.println("COMMAND_GET_CHANNEL_STR");
                    //a2i.write_data(ESP_COMMAND_ADDRESS, ACK);
                    //send_channel_info(current_channel_n);
                    //a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    //a2i.write_data(ESP_COMMAND_ADDRESS, EOT);
                    break;
                    
                case COMMAND_SEND_MESSAGE:
                    Serial.println("COMMAND_SEND_MESSAGE:");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    message = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    send_message_to_channel(message);
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
                    break;
            }
            lastAppleCommand = command_byte;
        }
        lastReadLoopTime = millis();
    }
}
