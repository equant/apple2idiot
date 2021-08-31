/*
blah blah blah
*/

#define DEBUG true

// Load Wi-Fi library
#include <WiFi.h>

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
#define ESP_COMMAND_ADDRESS 0		  // This is a hack see function unbusy_ram() for details
#define APPLE_COMMAND_ADDRESS 1
#define SHARED_RAM_START_ADDRESS 2
#define RAM_BUSY 666
#define MAX_STR_LEN 44    // arbitrary length.

#define COMMAND_GENERIC 0b10000000

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

const long readLoopInterval = 1000; // millis
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
    //Serial.print("    A:");        
    for (byte i=0; i<ADDRESS_BUS_SIZE; i++) {
        byte state = bitRead(address, i);
        digitalWrite(address_pins[i], state);
        //Serial.print(state);
    }
    //Serial.println();
    return true;
}

byte read_data(int address) {
    //Serial.print("READ: ");
    //Serial.println(address);        
    byte data_bus_read = 0;
    if (set_address(address)) {
        digitalWrite(RW_PIN, RW_READ);  // Should already be set to RW_READ, but just in case.
        //Serial.print("    D:");        
        for (byte i=0; i<DATA_BUS_SIZE; i++) {
            byte pin_state = digitalRead(data_pins[i]);
            data_bus_read += pin_state * pow(2,i);
            //Serial.print(pin_state);        
        }
        //Serial.println();
        ram_busy = false;
	unbusy_ram();
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
	unbusy_ram();
        return true;
    } else {
        return false;
    }
}


void send_string_to_apple(String string_to_send, int address) {
    //if (string_to_send.length() > 15 - 1) { // - 1 because of null character at end of string.
    write_data(ESP_COMMAND_ADDRESS, 12);
    int c = 0;
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

    //prefill_ram_with_pattern_data();

    Serial.println("-----------------------------------------");
    Serial.println("Sending string...");

    //delay(10); 

    send_string_to_apple("Starting Up!", SHARED_RAM_START_ADDRESS);
    Serial.println("-----------------------------------------");
    Serial.println("String sent.");
    //read_ram(16);
}

/*################################################
#                      Main                      #
################################################*/

char rot13Char(char ch) {
  if(ch >= 'A' && ch <= 'Z') return 'A' + (ch-'A'+13) % 26;  
  else if(ch >= 'a' && ch <= 'z') return 'a' + (ch-'a'+13) % 26;
  else return ch;
}

String rot13(String string_to_rot) {
    Serial.println("ROTIFY:"+string_to_rot);
    String new_string = "";
    for (int i=0; i < string_to_rot.length(); i++) {
        new_string += rot13Char(string_to_rot[i]);
    }
    Serial.println("ROTIED:"+new_string);
    return new_string;
}

void loop() {

    if ((millis() - lastReadLoopTime) > readLoopInterval) {
        byte command_byte = read_data(APPLE_COMMAND_ADDRESS);
        if (command_byte == RAM_BUSY) {
            Serial.println("Command Read: RAM BUSY");
        }
        else if (command_byte != lastAppleCommand){
            switch(command_byte) {
                case COMMAND_GENERIC:
                    String read_string = read_string_from_ram(SHARED_RAM_START_ADDRESS);
                    send_string_to_apple(rot13(read_string), SHARED_RAM_START_ADDRESS);
                    write_data(APPLE_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
                    break;
            }
            lastAppleCommand = command_byte;
            Serial.print("Command Read: ");
            Serial.println(command_byte);
            write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            write_data(ESP_COMMAND_ADDRESS, EOT);      // notify Apple IIe we are done processing command byte
        }
        lastReadLoopTime = millis();
    }
}
