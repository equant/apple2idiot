#include <Arduino.h>
#include "Apple2Idiot.h"

byte data_pins[] = {D7R, D6R, D5R, D4R, D3R, D2R, D1R, D0R};
byte address_pins[] = {A0R, A1R, A2R, A3R, A4R, A5R, A6R, A7R};
volatile byte ram_busy=0;
byte ram[256];

Apple2Idiot::Apple2Idiot() {
}

void Apple2Idiot::init() {
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

    write_string_to_shared_ram("Starting Up!", SHARED_RAM_START_ADDRESS);

    write_data(ESP_COMMAND_ADDRESS, ACK); 
    write_data(APPLE_COMMAND_ADDRESS, ACK);
}

void Apple2Idiot::unbusy_ram() {
	set_address(ESP_COMMAND_ADDRESS);
        ram_busy = false;
}

boolean Apple2Idiot::set_address(int address) {
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

byte Apple2Idiot::read_data(int address) {
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


boolean Apple2Idiot::write_data(byte address, byte byte_to_write) {
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


unsigned int Apple2Idiot::write_string_to_shared_ram(String string_to_send, unsigned int address) {
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

String Apple2Idiot::read_string_from_ram(int address) {
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

void Apple2Idiot::read_ram(int size_to_read) {
    for (int i=0; i < size_to_read; i++) {
        unsigned int foo = read_data(i);
        ram[i] = foo;
        Serial.print(i);
        Serial.print("    ");
        Serial.println(foo);
    }
}
