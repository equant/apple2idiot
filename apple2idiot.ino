/*
blah blah blah
*/

#define DEBUG true

// Load Wi-Fi library
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
//#include <WebServer.h>

//#include <IdiotHTML.h>


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


/*################################################
#                      ISR                       #
################################################*/

void IRAM_ATTR isrDEVSEL(void) {
    raw_register_read = REG_READ(GPIO_IN_REG);
    raw_register1_read = REG_READ(GPIO_IN1_REG);
    isr_handled = true;
}

unsigned long write_data(byte address, byte byte_to_write) {
    set_address(address);
    for (byte i=0; i<DATA_BUS_SIZE; i++) {
        byte bit_to_write = (byte_to_write >> i) & 0b00000001;
        pinMode(data_pins[i], OUTPUT);
        delay(10);
        digitalWrite(data_pins[i], bit_to_write);
    }
    digitalWrite(RW_PIN, RW_WRITE);
    delay(50);
    digitalWrite(RW_PIN, RW_READ);
    for (byte i=0; i<DATA_BUS_SIZE; i++) {
        pinMode(data_pins[i], INPUT);
    }
}


void store_ip_to_ram(byte offset) {
    IPAddress ip_address = WiFi.localIP();
    for (int i=0; i < ADDRESS_BUS_SIZE; i++) {
        write_data(i+offset, ip_address[i]);
        delay(100);
    }
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

    delay(100);
    //wifi_scan();

    /* Connect to wifi */
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting wifi...");
    Serial.print("  connecting to: ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
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
    web_server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Free Heap: " + String(ESP.getFreeHeap()) + " bytes.");
    });

    //web_server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
        //request->send(200, "text/plain", "Hello World");
    //});

    //web_server.on("/", www_root);
    web_server.begin();
    Serial.println("HTTP server started");
    delay(100); 

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
#                   Functions                    #
################################################*/

void set_address(int address) {
    //#if defined(DEBUG)
        //Serial.print("Setting address (");
        //Serial.print(address);
        //Serial.print("): ");
    //#endif
    for (byte i=0; i<16; i++) {
        byte state = bitRead(address, i);
        digitalWrite(address_pins[i], state);
        //#if defined(DEBUG)
            //Serial.print(state);
        //#endif
    }
    //#if defined(DEBUG)
        //Serial.println();
    //#endif
}

unsigned long read_data(int address) {
    unsigned long data_bus_read = 0;
    set_address(address);
    digitalWrite(RW_PIN, RW_READ);  // Should already be set to RW_READ, but just in case.
    for (byte i=0; i<DATA_BUS_SIZE; i++) {
        byte pin_state = digitalRead(data_pins[i]);
        data_bus_read += pin_state * pow(2,i);
    }
    return data_bus_read; 
}


/*################################################
#                      Main                      #
################################################*/

const long readLoopInterval = 7000; // millis
unsigned long lastReadLoopTime = 0;
//byte ram[ADDRESS_BUS_SIZE];
byte ram[16];

void read_ram() {
        for (int i=0; i < 16; i++) {
            byte foo = read_data(i);
            ram[i] = foo;
            delay(50);
        }
}

void loop() {
    //if (isr_handled) {
        //data_byte = raw_register_read >> 12 & 0b00000000000011111111;
        //isr_handled = false;
    //}
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
        Serial.println("Found address: "+address);
        if (request->hasParam("data")) {
            data_byte = request->getParam("data")->value();
            Serial.println("Found data: "+data_byte);
            write_data(address.toInt(), data_byte.toInt());
        }
    }
    request->send(SPIFFS, "/ram.htm", String(), false, html_template_processor);
}
void www_css(AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/a2i.css", "text/css");
}
