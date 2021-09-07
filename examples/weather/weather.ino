/*

Use this program with the Apple2idIOT card and the basic programs RRAM, WRAM and CMDROT to read/write and rot13
a single string contained within the dual port ram on the card.

*/

#define DEBUG true

// Load Wi-Fi library
#include <WiFi.h>

/**********************/
/* Default WiFi       */
/**********************/

// Replace with your network credentials
const char* wifi_ssid = "ella";
const char* wifi_password = "";

/**************/
/* ESP32 Pins */
/**************/

/* DATA BUS (numbers mean GPIO port) */
#define D0R 12
#define D1R 13
#define D2R 14
#define D3R 15
#define D4R 16
#define D5R 17
#define D6R 18
#define D7R 19
byte data_pins[] = {D7R, D6R, D5R, D4R, D3R, D2R, D1R, D0R};
#define DATA_BUS_SIZE 8

/* Address Bus */
#define A0R 21
#define A1R 22
#define A2R 23
#define A3R 25
#define A4R 26
#define A5R 27
#define A6R 32
#define A7R 33
byte address_pins[] = {A0R, A1R, A2R, A3R, A4R, A5R, A6R, A7R};
#define ADDRESS_BUS_SIZE 8
#define ESP_COMMAND_ADDRESS 0
#define APPLE_COMMAND_ADDRESS 1
#define SHARED_RAM_START_ADDRESS 2
#define RAM_BUSY 666
#define MAX_STR_LEN 44    // arbitrary length.

#define COMMAND_GENERIC 0b10000000
#define COMMAND_SCAN_WIFI 111
#define COMMAND_CONNECT 112

/* IDT7132S dual port ram chip enable */
#define RW_PIN      5
#define RW_WRITE    LOW
#define RW_READ     HIGH

#define INPUT_35 35
#define INPUT_34 34

#define ETX 3   // ASCII "End of Text" (ETX) character
#define ACK 0b00000110  // Acknowledge
#define EOT 0b00000100  // End of transmit

/*********/
/* Misc. */
/*********/

const long readLoopInterval = 100; // millis
unsigned long lastReadLoopTime = 0;
byte ram[256];
volatile byte ram_busy=0;

byte lastAppleCommand = 0;

/*################################################
#                   Functions                    #
################################################*/

void unbusy_ram() {
	set_address(ESP_COMMAND_ADDRESS);
        ram_busy = false;
}

boolean set_address(int address) {
    if (ram_busy) {
        Serial.println("BUSY");        
        return false;
    }
    ram_busy = true;
    for (byte i=0; i<ADDRESS_BUS_SIZE; i++) {
        byte state = bitRead(address, i);
        digitalWrite(address_pins[i], state);
    }
    return true;
}

byte read_data(int address) {
    byte data_bus_read = 0;
    if (set_address(address)) {
        digitalWrite(RW_PIN, RW_READ);  // Should already be set to RW_READ, but just in case.
        for (byte i=0; i<DATA_BUS_SIZE; i++) {
            byte pin_state = digitalRead(data_pins[i]);
            data_bus_read += pin_state * pow(2,i);
        }
        ram_busy = false;
	unbusy_ram();
        return data_bus_read; 
    } else {
        return RAM_BUSY;
    }
}


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
	unbusy_ram();
        return true;
    } else {
        return false;
    }
}


unsigned int write_string_to_shared_ram(String string_to_send, unsigned int address) {
    //if (string_to_send.length() > 15 - 1) { // - 1 because of null character at end of string.
    write_data(ESP_COMMAND_ADDRESS, 12);
    unsigned int c = 0;
    for (c=0; c < string_to_send.length(); c++) {
        Serial.print("A(");
        Serial.print(c);
        Serial.print("): ");
        Serial.println(string_to_send[c]);
        write_data(address+c, string_to_send[c]);
    }
    write_data(address+c, ETX);
    //write_data(15, COMMAND_FROM_ESP + command_message + COMMAND_NO_DATA_WAITING);
    write_data(ESP_COMMAND_ADDRESS, 27);
    return address+c;
}

String read_string_from_ram(int address) {
    byte c = 0;
    int i = 0;
    String read_string = "";
    while ( (i<MAX_STR_LEN) && (c!=ETX) ) {
        c = read_data(address+i);
        read_string = read_string + char(c);
        i++;
    }
    Serial.print("READ STRING:");
    Serial.println(read_string);
    return read_string;
}

void read_ram(int size_to_read=256);
void read_ram(int size_to_read) {
    for (int i=0; i < size_to_read; i++) {
        unsigned int foo = read_data(i);
        ram[i] = foo;
        Serial.print(i);
        Serial.print("    ");
        Serial.println(foo);
    }
}


/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);

    /* Configure ESP32 Pins */
    pinMode(A0R, OUTPUT); digitalWrite(A0R, LOW);
    pinMode(A1R, OUTPUT); digitalWrite(A1R, LOW);
    pinMode(A2R, OUTPUT); digitalWrite(A2R, LOW);
    pinMode(A3R, OUTPUT); digitalWrite(A3R, LOW);
    pinMode(A4R, OUTPUT); digitalWrite(A4R, LOW);
    pinMode(A5R, OUTPUT); digitalWrite(A5R, LOW);
    pinMode(A6R, OUTPUT); digitalWrite(A6R, LOW);
    pinMode(A7R, OUTPUT); digitalWrite(A7R, LOW);
    pinMode(D0R, INPUT);
    pinMode(D1R, INPUT);
    pinMode(D2R, INPUT);
    pinMode(D3R, INPUT);
    pinMode(D4R, INPUT);
    pinMode(D5R, INPUT);
    pinMode(D6R, INPUT);
    pinMode(D7R, INPUT);
    pinMode(RW_PIN, OUTPUT); digitalWrite(RW_PIN, RW_READ);

    pinMode(INPUT_34, INPUT);
    pinMode(INPUT_35, INPUT);

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
    
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(10);

    write_string_to_shared_ram("Starting Up!", SHARED_RAM_START_ADDRESS);
    write_data(ESP_COMMAND_ADDRESS, ACK); 
    write_data(APPLE_COMMAND_ADDRESS, ACK);

    Serial.println("Setup done");
}

/*################################################
#                      Main                      #
################################################*/

void scan_wifi() {
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    int address_counter = SHARED_RAM_START_ADDRESS + 1;
    if (n == 0) {
        Serial.println("no networks found");
        write_data(0, address_counter);
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        write_data(n, address_counter);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
            address_counter = write_string_to_shared_ram(WiFi.SSID(i), address_counter + 1);
            //address_counter = write_string_to_shared_ram(String(WiFi.RSSI(i)), address_counter + 1);
            //address_counter = write_string_to_shared_ram(WiFi.encryptionType(i), address_counter + 1);
        }
    }
    write_data(ESP_COMMAND_ADDRESS, EOT);
    Serial.println("");
}

void store_ip_to_ram(byte offset) {
    IPAddress ip_address = WiFi.localIP();
    //for (int i=0; i < ADDRESS_BUS_SIZE; i++) {
    for (int i=0; i < 4; i++) {
        write_data(i+offset, ip_address[i]);
    }
}

const char* wifi_ssid = "";
const char* wifi_password = "";

void loop() {

    if ((millis() - lastReadLoopTime) > readLoopInterval) {
        byte command_byte = read_data(APPLE_COMMAND_ADDRESS);
        if (command_byte == RAM_BUSY) {
            Serial.println("Command Read: RAM BUSY");
        }
        else if (command_byte != lastAppleCommand){
            Serial.print("Command Switch command_byte: ");
            Serial.println(command_byte);
            switch(command_byte) {
                case COMMAND_SCAN_WIFI:
                    write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    //String read_string = read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    //write_string_to_shared_ram(rot13(read_string), SHARED_RAM_START_ADDRESS);
                    scan_wifi();
                    write_data(APPLE_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    break;
            }
            switch(command_byte) {
                case COMMAND_CONNECT:
                    write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    int access_point_n = read_data(SHARED_RAM_START_ADDRESS);
                    String ssid_as_String = WiFi.SSID(access_point_n);
                    String password_as_String = read_string_from_ram(SHARED_RAM_START_ADDRESS+1);
                    wifi_password = password_as_String.c_str();
                    wifi_ssid = ssid_as_String.c_str();
                    //wifi_password = read_string_from_ram(SHARED_RAM_START_ADDRESS+1);
                    //wifi_ssid = WiFi.SSID(access_point_n);
                    //WiFi.begin(wifi_ssid, wifi_password);
                    Serial.print("password:");
                    Serial.println(password_as_String);
                    Serial.print("password:(");
                    Serial.print(wifi_password);
                    Serial.println(")");
                    //WiFi.begin(wifi_ssid, wifi_password);
                    WiFi.begin("GSO", "xerxes27");
                    while (WiFi.status() != WL_CONNECTED) {
                        delay(300);
                        Serial.print(".");
                    }
                    Serial.println("");
                    Serial.println("WiFi connected successfully");
                    Serial.print("Got IP: ");
                    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
                    store_ip_to_ram(SHARED_RAM_START_ADDRESS);
                    write_data(APPLE_COMMAND_ADDRESS, ACK);
                    break;
            }
            lastAppleCommand = command_byte;
            write_data(ESP_COMMAND_ADDRESS, EOT);      // notify Apple IIe we are done processing command byte
        }
        lastReadLoopTime = millis();
    }
}
