/*
blah blah blah
*/

#define DEBUG true

// Load Wi-Fi library
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/**************/
/* ESP32 Pins */
/**************/

/* DATA BUS (numbers mean GPIO port) */
#define D0R 12
#define D1R 13
#define D2R 14
#define D3R 15
#define D4R 18
#define D5R 19
#define D6R 21
#define D7R 22
byte data_pins[] = {D0R, D1R, D2R, D3R, D4R, D5R, D6R, D7R};
#define DATA_BUS_SIZE 8

/* Address Bus */
#define A0R 23
#define A1R 25
#define A2R 26
#define A3R 27
byte address_pins[] = {A0R, A1R, A2R, A3R};
#define ADDRESS_BUS_SIZE 4

/* IDT7132S dual port ram chip enable */
#define RW_PIN      5
#define RW_WRITE    LOW
#define RW_READ     HIGH

unsigned int data_byte = 0;
                                            //    fisrt bit is a flag for if the data is from Apple or from ESP32.
                                            //   /     
                                            //  /       last bit is a flag for "more data waiting to be sent".
                                            // /       /
#define COMMAND_FROM_APPLE          0       // 0_______
#define COMMAND_FROM_ESP          128       // 1_______
#define COMMAND_MORE_DATA_WAITING   1       // _0000001
#define COMMAND_NO_DATA_WAITING     0       // _0000001

#define COMMAND_GENERIC_MESSAGE     2       // _000001_
#define COMMAND_FETCH_WEATHER       4       // _000010_
#define COMMAND_SEND_LONG_STRING   12       // _000110_
#define COMMAND_FORMAT_RAM        126       // _111111_

#define ETX 3   // ASCII "End of Text" (ETX) character

/************/
/* Interupt */
/************/

/* Variables shared between ISR and main code need to be volatile */
volatile bool isr_handled = false;
volatile uint32_t raw_register_read;
volatile uint16_t raw_register1_read;

/**********************/
/* WiFi and Webserver */
/**********************/

// Replace with your network credentials
const char* wifi_ssid = "GSO";
const char* wifi_password = "xerxes27";
AsyncWebServer web_server(80);
//WebServer web_server(80);

/*******************/
/* Weather Service */
/*******************/

const String weather_service_api_key= "0ab97bbbea58592d7c9d64067a34d2d0";
const String weather_url = "http://api.openweathermap.org/data/2.5/weather?";

/*********/
/* Misc. */
/*********/

const long readLoopInterval = 10000; // millis
unsigned long lastReadLoopTime = 0;
//byte ram[ADDRESS_BUS_SIZE];
byte ram[16];
volatile byte ram_busy=0;
//const unsigned int RAM_BUSY=666;
#define RAM_BUSY 666

/*################################################
#                      ISR                       #
################################################*/

void IRAM_ATTR isrDEVSEL(void) {
    raw_register_read = REG_READ(GPIO_IN_REG);
    raw_register1_read = REG_READ(GPIO_IN1_REG);
    isr_handled = true;
}

/*################################################
#                   Functions                    #
################################################*/

boolean set_address(int address) {
    if (ram_busy) {
        Serial.println("BUSY");        
        return false;
    }
    ram_busy = true;
    //Serial.print("    Setting address (");
    //Serial.print(address);
    //Serial.println(")");
    //delay(20);
    Serial.print("    A:");        
    for (byte i=0; i<ADDRESS_BUS_SIZE; i++) {
        byte state = bitRead(address, i);
        digitalWrite(address_pins[i], state);
        Serial.print(state);
    }
    Serial.println();
    return true;
}

unsigned int read_data(int address) {
    Serial.print("READ: ");
    Serial.println(address);        
    byte data_bus_read = 0;
    if (set_address(address)) {
        digitalWrite(RW_PIN, RW_READ);  // Should already be set to RW_READ, but just in case.
        Serial.print("    D:");        
        for (byte i=0; i<DATA_BUS_SIZE; i++) {
            byte pin_state = digitalRead(data_pins[i]);
            data_bus_read += pin_state * pow(2,i);
            Serial.print(pin_state);        
        }
        Serial.println();
        ram_busy = false;
        return data_bus_read; 
    } else {
        return RAM_BUSY;
    }
}

//signed int convert_to_signed_byte(byte byte_to_convert) {
    //if (abs(requested_byte_to_write) > 127) {
    //if (requested_byte_to_write < 0) {

boolean write_data(byte address, byte byte_to_write) {
    Serial.print("WRITE: ");
    Serial.print(byte_to_write);        
    Serial.print(" -> ");
    Serial.println(address);        
    if (set_address(address)) {
        //set_address(address);
        Serial.print("    D:");        
        for (byte i=0; i<DATA_BUS_SIZE; i++) {
            byte bit_to_write = (byte_to_write >> i) & 0b00000001;
            pinMode(data_pins[i], OUTPUT);
            digitalWrite(data_pins[i], bit_to_write);
            Serial.print(bit_to_write);        
        }
        Serial.println();        
        digitalWrite(RW_PIN, RW_WRITE);
        delay(1);
        digitalWrite(RW_PIN, RW_READ);
        for (byte i=0; i<DATA_BUS_SIZE; i++) {
            pinMode(data_pins[i], INPUT);
        }
        ram_busy = false;
        return true;
    } else {
        return false;
    }
}


void store_ip_to_ram(byte offset) {
    IPAddress ip_address = WiFi.localIP();
    for (int i=0; i < ADDRESS_BUS_SIZE; i++) {
        write_data(i+offset, ip_address[i]);
    }
}

void send_string_to_apple(String string_to_send, byte command_message) {
    if (string_to_send.length() > 15 - 1) { // - 1 because of null character at end of string.
    } else {
        int c=0;
        for (c=0; c < string_to_send.length(); c++) {
            write_data(c, string_to_send[c]);
        }
        write_data(c+1, ETX);
        write_data(15, COMMAND_FROM_ESP + command_message + COMMAND_NO_DATA_WAITING);
    }
}

void fetch_weather(char* city_name) {
    HTTPClient http;
    //http.begin(String(weather_url) + "?q=Tucson,us&APPID=" + String(weather_service_api_key));
    const String request_url = weather_url + "q=Tucson,us&APPID=" + weather_service_api_key;
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
            //const char* main = doc["main"];
            Serial.println("----------------------");
            serializeJsonPretty(doc, Serial);
            Serial.println("----------------------");
            serializeJsonPretty(doc["wind"], Serial);
            Serial.println("----------------------");
            int temp       = doc["main"]["humidity"];
            int humidity   = doc["main"]["humidity"];
            float wind_speed = doc["wind"]["speed"];
            int wind_deg   = doc["wind"]["speed"];
            String weather_description = doc["weather"][0]["description"];
            write_data(0, round(temp-273.15));
            write_data(1, round(humidity));
            write_data(2, round(wind_deg/10));      // divide by twn because 360 is too big for 8 bits
            write_data(3, round(wind_speed));
                
        }

    }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
}

void read_ram() {
    for (int i=0; i < 16; i++) {
        unsigned int foo = read_data(i);
        ram[i] = foo;
    }
}

String html_template_processor(const String& var) {
    Serial.println("html_template_processor()");
    String return_string = "";
    if (var == "RAM_TABLE") {
        read_ram();
        for (int i=0; i < 16; i++) {
            return_string += "<tr><td>"+String(i)+"</td><td>" + String(ram[i]) + "</td></tr>\n";
        }
        return return_string;
    }
    return var;
}
        

void www_weather(AsyncWebServerRequest *request) {
    fetch_weather("Tucson");
    request->send(SPIFFS, "/ram.htm", String(), false, html_template_processor);
}
void www_root(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.htm", String(), false, html_template_processor);
}
void www_ram(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/ram.htm", String(), false, html_template_processor);
}
void www_write_byte(AsyncWebServerRequest *request) {
    Serial.println("www_write_byte()");
    String address;
    String data_byte;
    if (request->hasParam("address")) {
        address = request->getParam("address")->value();
        //Serial.println("Found address: "+address);
        if (request->hasParam("data")) {
            data_byte = request->getParam("data")->value();
            //Serial.println("Found data: "+data_byte);
            write_data(address.toInt(), data_byte.toInt());
        }
    }
    request->send(SPIFFS, "/ram.htm", String(), false, html_template_processor);
}
void www_css(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/a2i.css", "text/css");
}

void prefill_ram_with_pattern_data() {
    write_data(15, 0);      // notify Apple IIe we are done processing command byte
    write_data(14, 123);      // notify Apple IIe we are done processing command byte
    write_data(13, 1);      // notify Apple IIe we are done processing command byte
    write_data(12, 123);      // notify Apple IIe we are done processing command byte
    write_data(11, 2);      // notify Apple IIe we are done processing command byte
    write_data(10, 123);      // notify Apple IIe we are done processing command byte
    write_data(9, 3);      // notify Apple IIe we are done processing command byte
    write_data(8, 123);      // notify Apple IIe we are done processing command byte
    write_data(7, 4);      // notify Apple IIe we are done processing command byte
    write_data(6, 123);      // notify Apple IIe we are done processing command byte
    write_data(5, 5);      // notify Apple IIe we are done processing command byte
    write_data(4, 123);      // notify Apple IIe we are done processing command byte
    write_data(3, 6);      // notify Apple IIe we are done processing command byte
    write_data(2, 123);      // notify Apple IIe we are done processing command byte
    write_data(1, 7);      // notify Apple IIe we are done processing command byte
    write_data(0, 123);      // notify Apple IIe we are done processing command byte
}

/*################################################
#                     Setup                      #
################################################*/

void setup() {

    /* Configure ESP32 Pins */
    pinMode(A0R, OUTPUT); digitalWrite(A0R, LOW);
    pinMode(A1R, OUTPUT); digitalWrite(A1R, LOW);
    pinMode(A2R, OUTPUT); digitalWrite(A2R, LOW);
    pinMode(A3R, OUTPUT); digitalWrite(A3R, LOW);
    pinMode(D0R, INPUT);
    pinMode(D1R, INPUT);
    pinMode(D2R, INPUT);
    pinMode(D3R, INPUT);
    pinMode(D4R, INPUT);
    pinMode(D5R, INPUT);
    pinMode(D6R, INPUT);
    pinMode(D7R, INPUT);
    pinMode(RW_PIN, OUTPUT); digitalWrite(RW_PIN, RW_READ);

    delay(10);
    //wifi_scan();

    /* Connect to wifi */
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting wifi...");
    Serial.print("  connecting to: ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(900);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
    prefill_ram_with_pattern_data();
    store_ip_to_ram(0);
    //store_ip_to_ram(4);

    /* Start webserver */
    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
    }
    web_server.on("/", HTTP_GET, www_root);
    web_server.on("/a2i.css", HTTP_GET, www_css);
    web_server.on("/ram", HTTP_GET, www_ram);
    web_server.on("/write_byte", HTTP_GET, www_write_byte);
    web_server.on("/weather", HTTP_GET, www_weather);
    web_server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Free Heap: " + String(ESP.getFreeHeap()) + " bytes.");
    });

    //web_server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
        //request->send(200, "text/plain", "Hello World");
    //});

    //web_server.on("/", www_root);
    web_server.begin();
    Serial.println("HTTP server started");
    delay(10); 

    /* Display file system contents */
    Serial.println("-----------------------------------------");
    File root_filesystem = SPIFFS.open("/");
    File f = root_filesystem.openNextFile();
    while(f){
        Serial.print("FILE: ");
        Serial.println(f.name());
        f = root_filesystem.openNextFile();
    }
    Serial.println("-----------------------------------------");

    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, LOW);
}

/*################################################
#                      Main                      #
################################################*/

void loop() {
    //if (isr_handled) {
        //data_byte = raw_register_read >> 12 & 0b00000000000011111111;
        //isr_handled = false;
    //}

    if ((millis() - lastReadLoopTime) > readLoopInterval) {
        //Serial.println("+++");
        unsigned int command_byte = read_data(15);
        if (command_byte == RAM_BUSY) {
            Serial.println("Command Read: RAM BUSY");
        }
        else if (command_byte < COMMAND_FROM_ESP) {
            // command came from apple (or webform).
            Serial.print("Command Read: ");
            Serial.println(command_byte);
            //write_data(15, 1);      // notify Apple IIe we are processing command byte
            switch(command_byte) {
                case COMMAND_FETCH_WEATHER:
                    Serial.println("Fetch Weather");
                    fetch_weather("Tucson");
                    break;
                case COMMAND_SEND_LONG_STRING:
                    //send_string_to_apple("This is a long string", COMMAND_GENERIC_MESSAGE); 
                    send_string_to_apple("ABCDE", COMMAND_GENERIC_MESSAGE); 
                case COMMAND_FORMAT_RAM:
                    Serial.println("Calling prefill_ram_with_pattern_data()");
                    prefill_ram_with_pattern_data();
                    write_data(15, 0);      // notify Apple IIe we are done processing command byte
                    break;
            }
            /*
            byte c = 0;
            while (ram_busy && (c < 10)) {
                delay(10);
                c = c+1;
                Serial.print("_");
            }
            Serial.println("^^^^");
            write_data(15, 0);      // notify Apple IIe we are done processing command byte
            read_data(15);      // notify Apple IIe we are done processing command byte
            */
        }
        lastReadLoopTime = millis();
    }
}
