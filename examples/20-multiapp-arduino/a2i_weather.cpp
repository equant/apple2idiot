#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Apple2Idiot.h>
#include "weather_commands.h"
#include "a2i_weather.h"
#include "credentials.h"


void Weather::init(Apple2Idiot *a2ip, HTTPClient *httpp) {
    a2i  = a2ip;
    http = httpp;
    Serial.println("WEATHER()::init()");
}

byte Weather::handleCommand(byte command) {
    Serial.println("WEATHER() handleCommand");
    switch(command) {
        case COMMAND_FETCH_WEATHER: {
            Serial.println("WEATHER() COMMAND_FETCH_WEATHER");
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            Serial.println("WEATHER() before fetch_weather()");
            return fetch_weather();
        }
        case COMMAND_SET_COUNTRY: {
            Serial.println("WEATHER() COMMAND_SET_COUNTRY");
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            country_code = a2i->read_string_from_ram(SHARED_RAM_START_ADDRESS);
            Serial.println("Received CountryCode: ["+country_code+"]");
            a2i->write_data(APPLE_COMMAND_ADDRESS, ACK);
            a2i->write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
            return ACK;
            //break;
        }
        case COMMAND_SET_CITY: {
            //a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            Serial.print("WEATHER() COMMAND_SET_CITY");
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            city_name = a2i->read_string_from_ram(SHARED_RAM_START_ADDRESS);
            Serial.println("Received CityName: ["+city_name+"]");
            a2i->write_data(APPLE_COMMAND_ADDRESS, ACK);
            a2i->write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
            return ACK;
        }
        default: {
            Serial.print("WEATHER() COMMAND_NOT_FOUND: ");
            Serial.println(command);        
            return COMMAND_NOT_FOUND;
        }
    }
}

byte Weather::fetch_weather() {

    byte result = 0;
    Apple2Idiot a2i;
    HTTPClient http;

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%sq=%s,%s&APPID=%s", api_entry_point, city_name, country_code, WEATHER_ACCESS_TOKEN);
    //sprintf(api_request, "http://api.openweathermap.org/data/2.5/weather?q=TUCSON,US&APPID=0ab97bbbea58592d7c9d64067a34d2d0");
    Serial.print("    "); Serial.println(api_request);
    http.begin(api_request);

    int httpCode = http.GET();  //Make the request
    Serial.print("    "); Serial.println("After GET()");
    delay(10);

    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        //Serial.println(httpCode);
        Serial.println("++++++++++++++++++++++++");
        Serial.println(payload);
        Serial.println("++++++++++++++++++++++++");
        StaticJsonDocument<200> filter;
        filter["weather"][0]["main"]        = true;
        filter["weather"][0]["description"] = true;
        filter["main"]["humidity"]          = true;
        filter["main"]["temp"]              = true;
        filter["wind"]["speed"]             = true;
        filter["wind"]["deg"]               = true;
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
            serializeJsonPretty(doc["wind"], Serial);
            Serial.println("----------------------");
            String temp       = doc["main"]["temp"];
            String humidity   = doc["main"]["humidity"];
            String wind_speed = doc["wind"]["speed"];
            String wind_deg   = doc["wind"]["deg"];
            String weather_description1 = doc["weather"][0]["main"];
            String weather_description2 = doc["weather"][0]["description"];
            int address_counter = a2i.write_string_to_shared_ram(temp, SHARED_RAM_START_ADDRESS);
            address_counter = a2i.write_string_to_shared_ram(humidity, address_counter + 1);
            address_counter = a2i.write_string_to_shared_ram(wind_speed, address_counter + 1);
            address_counter = a2i.write_string_to_shared_ram(wind_deg, address_counter + 1);
            address_counter = a2i.write_string_to_shared_ram(weather_description1, address_counter + 1);
            address_counter = a2i.write_string_to_shared_ram(weather_description2, address_counter + 1);
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

