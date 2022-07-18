#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Apple2Idiot.h>
#include "iss_commands.h"
#include "a2i_iss.h"


void Iss::init(Apple2Idiot *a2ip, HTTPClient *httpp) {
    a2i  = a2ip;
    http = httpp;
    Serial.println("ISS()::init()");
}

byte Iss::handleCommand(byte command) {
    Serial.println("ISS() handleCommand");
    switch(command) {
        case COMMAND_GET_ISS: {
            Serial.println("ISS() COMMAND_GET_ISS");
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            Serial.println("ISS() before fetch_iss()");
            return fetch_iss();
        }
        default: {
            Serial.print("ISS() COMMAND_NOT_FOUND: ");
            Serial.println(command);        
            return COMMAND_NOT_FOUND;
        }
    }
}

byte Iss::fetch_iss() {

    byte result = 0;
    Apple2Idiot a2i;
    HTTPClient http;

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s", api_entry_point);
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
        filter["iss_position"]["latitude"]  = true;
        filter["iss_position"]["longitude"] = true;
        filter["timestamp"]                 = true;
        filter["message"]["humidity"]       = true;
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
            serializeJsonPretty(doc["iss_position"], Serial);
            Serial.println("----------------------");
            String latitude  = doc["iss_position"]["latitude"];
            String longitude = doc["iss_position"]["longitude"];
            String timestamp = doc["timestamp"];
            String message   = doc["messasge"];
            int address_counter = a2i.write_string_to_shared_ram(latitude, SHARED_RAM_START_ADDRESS);
            address_counter = a2i.write_string_to_shared_ram(longitude, address_counter + 1);
            address_counter = a2i.write_string_to_shared_ram(timestamp, address_counter + 1);
            address_counter = a2i.write_string_to_shared_ram(message, address_counter + 1);
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

