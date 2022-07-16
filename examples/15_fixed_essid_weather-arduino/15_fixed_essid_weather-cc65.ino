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

Apple2Idiot a2i = Apple2Idiot();

#define COMMAND_SET_COUNTRY 200
#define COMMAND_SET_CITY 201
#define COMMAND_FETCH_WEATHER 205

#include "credentials.h"

//const char* wifi_ssid = "HotelMcCoy-Guest";
//const char* wifi_password = "travelforall";
char wifi_ssid[] = WIFI_SSID;         // your network SSID (name)
char wifi_password[] = WIFI_PASSWORD; // your network password

/*******************/
/* Weather Service */
/*******************/

const String weather_service_api_key= "0ab97bbbea58592d7c9d64067a34d2d0";
const String weather_url = "http://api.openweathermap.org/data/2.5/weather?";

String country_code = "US";
String city_name = "Tucson";

/*******************/
/*    Misc         */
/*******************/

const long readLoopInterval = 100; // millis
unsigned long lastReadLoopTime = 0;

byte lastAppleCommand = 0;

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.println("Starting 15_fixed_essid_weather-cc65.ino after a quick delay so that we have time to connect a serial monitor after restart and see what's going on");
    delay(3000);
    Serial.println("Starting 15_fixed_essid_weather-cc65.ino");

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
    
    Serial.println("Setup done");
}

/*################################################
#                   Functions                    #
################################################*/

byte fetch_weather() {

    byte result = 0;
    HTTPClient http;
    //const String request_url = weather_url + "q=Tucson,us&APPID=" + weather_service_api_key;
    const String request_url = weather_url + "q=" + city_name + "," + country_code + "&APPID=" + WEATHER_ACCESS_TOKEN;
    Serial.println(request_url);
    http.begin(request_url);
    int httpCode = http.GET();  //Make the request
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


/*################################################
#                      Main                      #
################################################*/

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
                case COMMAND_SET_COUNTRY:
                    Serial.println("COMMAND_SET_COUNTRY");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    country_code = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    Serial.println("Received: ["+country_code+"]");
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
                    break;
                case COMMAND_SET_CITY:
                    Serial.println("COMMAND_SET_CITY");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    city_name = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    Serial.println("Received: ["+city_name+"]");
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, EOT);   // notify Apple IIe we are done processing command byte
                    break;
                case COMMAND_FETCH_WEATHER:
                    Serial.println("COMMAND_FETCH_WEATHER");
                    a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    result = fetch_weather();
                    a2i.write_data(APPLE_COMMAND_ADDRESS, ACK);
                    a2i.write_data(ESP_COMMAND_ADDRESS, result);   // notify Apple IIe we are done processing command byte
                    break;
            }
            lastAppleCommand = command_byte;
        }
        lastReadLoopTime = millis();
    }
}
