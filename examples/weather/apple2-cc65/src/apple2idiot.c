#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <peekpoke.h>

#include "globals.h"
#include "apple2idiot.h"

#define MAX_STR_LEN 250


unsigned char read_byte(unsigned int address) {
    gotoxy(0,2);
    //printf("read_data(%u)", address);
}

unsigned char write_byte(unsigned int address, unsigned char byte_to_write) {
    //printf("%u <- %d, [%c]\n", address, byte_to_write, byte_to_write);
    POKE(address, byte_to_write);
}

unsigned char* write_string_to_ram(unsigned int address, char* string_to_send) {
	unsigned char i;
    unsigned char size = strlen(string_to_send);
    gotoxy(0,2);
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
    gotoxy(0,2);
    //printf("A: %u, L: %c\n", address, length);
    //cgetc();
    for (i=0; i<length; i++) {
        c = PEEK(address + i);    
        data[i] = c;
        if (c == 0) {
            break;
        }
    } 
}
