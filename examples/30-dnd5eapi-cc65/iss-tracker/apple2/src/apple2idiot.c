#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <peekpoke.h>

//#include "globals.h"
#include "apple2idiot.h"
//#include "../../../../arduino-lib/Apple2Idiot/A2I_commands.h"

#define MAX_STR_LEN 250

#define CARD_ADDRESS 0xC200
#define APPLE_COMMAND_ADDRESS 0xC201
#define RAM_DATA_START_ADDRESS 0xC202
#define ESP_TIMEOUT 5555
#define ACK 6               // Acknowledge
#define APP_ID = 202

unsigned int read_byte(unsigned int address) {
    unsigned int b = 0;
    b = PEEK(address);    
    //printf("read_data(%u)", address);
    return b;
}

unsigned char write_byte(unsigned int address, unsigned char byte_to_write) {
    //printf("%u <- %d, [%c]\n", address, byte_to_write, byte_to_write);
    POKE(address, byte_to_write);
}

unsigned char write_byte_wait_for_ack(unsigned int address, unsigned char byte_to_write) {
    unsigned char received_esp_response = 0;
    int timeout_count = 0;
    unsigned char timeout_happened = 0;
    int delay_count = 0;
    unsigned char read_char;
    write_byte(address, byte_to_write);
    while ((received_esp_response==0) || (timeout_happened==0)) {
        timeout_count++;
        if (timeout_count > ESP_TIMEOUT) {
            timeout_happened = 1;
            return 0;
        }
        //read_char = read_byte(ESP_COMMAND_ADDRESS);
        read_char = read_byte(APPLE_COMMAND_ADDRESS);
        if (read_char == ACK) {
            received_esp_response = 1;
            return 1;
        }
        for (delay_count=0; delay_count < 1111; ++delay_count) {
            // do nothing
        }
    }
}

unsigned char* write_string_to_ram(unsigned int address, char* string_to_send) {
	unsigned char i;
    unsigned char size = strlen(string_to_send);
    //gotoxy(0,2);
    if (string_to_send[size-1] == '\n') {
        string_to_send[size-1] = '\0';
    }
    //printf("%u (%s)\n", address, string_to_send);
    for (i=0; i<size; i++) {
        write_byte(address+i, string_to_send[i]);
    }
    if (string_to_send[size-1] != '\0') {
        write_byte(address+i, '\0');
    }
}

// HOW DO I PASS THE ADDRESS TO read_string_from_ram ???

void read_string_from_ram(unsigned int address, char *data, char length) {
    unsigned char c, i;
    //gotoxy(0,0);
    //printf("A: %u, L: %u\n", address, length);
    //cgetc();
    for (i=0; i<length; i++) {
        c = PEEK(address + i);    
        //printf("PEEK[%u]: %c\n", i, c);
        data[i] = c;
        if (c == 0) {
            break;
        }
    } 
}
