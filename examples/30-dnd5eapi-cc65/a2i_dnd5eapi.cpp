#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Apple2Idiot.h>
#include "dnd5eapi_commands.h"
#include "a2i_dnd5eapi.h"


void Dnd5eapi::init(Apple2Idiot *a2ip, HTTPClient *httpp) {
    a2i  = a2ip;
    http = httpp;
    Serial.println("DND5EAPI()::init()");
}

byte Dnd5eapi::handleCommand(byte command) {
    Serial.println("DND5EAPI() handleCommand");
    switch(command) {
        case COMMAND_SEARCH_MONSTER: {
            Serial.println("DND5EAPI() COMMAND_SEARCH_MONSTER");
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            Serial.println("DND5EAPI() searchMonster()");
            return searchMonster();
        }
        default: {
            Serial.print("DND5EAPI() COMMAND_NOT_FOUND: ");
            Serial.println(command);        
            return COMMAND_NOT_FOUND;
        }
    }
}

byte Dnd5eapi::searchMonster() {

    byte result = 0;
    Apple2Idiot a2i;
    HTTPClient http;

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/monsters?name=%s", api_entry_point, monster_search_string);
    Serial.print("    "); Serial.println(api_request);
    http.begin(api_request);

    int httpCode = http.GET();  //Make the request
    Serial.print("    "); Serial.println("After GET()");
    delay(10);
    Serial.print("    httpCode:"); Serial.println(httpCode);

    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        //Serial.println(httpCode);
        Serial.println("++++++++++++++++++++++++");
        Serial.println(payload);
        Serial.println("++++++++++++++++++++++++");
        StaticJsonDocument<200> filter;
        filter["count"] = true;
        filter["results"] = true;
        StaticJsonDocument<400> doc;
        DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        //DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        } else {
            Serial.println("----------------------");
            serializeJsonPretty(doc, Serial);
            Serial.println("----------------------");
            serializeJsonPretty(doc["results"], Serial);
            Serial.println("----------------------");
            int result_count  = doc["count"];
            String results = doc["results"];

            /// Write to ram
            int address_counter = SHARED_RAM_START_ADDRESS + 1;
            if (result_count == 0) {
                Serial.println("no monsters found");
                a2i.write_data(0, SHARED_RAM_START_ADDRESS);
            } else {
                a2i.write_data(result_count, address_counter);
                for (int i = 0; i < result_count; ++i) {
                    Serial.print(i + 1);
                    Serial.print(": ");
                    Serial.println(doc["results"][i]["index"].as<String>());
                    //delay(10);
                    address_counter = a2i.write_string_to_shared_ram(doc["results"][i]["index"].as<String>(), address_counter + 1);
                }
            }
        }
        result = ACK;
    }
    else {
        Serial.println("Error on HTTP request");
        result = ERR;
    }
 
    http.end(); //Free the resources
    return result;
}

