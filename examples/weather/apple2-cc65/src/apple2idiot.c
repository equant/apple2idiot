#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <peekpoke.h>

#include "globals.h"
#include "apple2idiot.h"

unsigned char read_data(unsigned char address) {
    gotoxy(0,2);
    printf("read_data()");
}

unsigned char write_data(unsigned char address, unsigned char byte_to_write) {
    printf("%d [%c]\n", address, byte_to_write);
    POKE(address, byte_to_write);
    //for (i=0;i<8;i++)
    //{
        //p = PEEK(0xC200+i);
        //printf("(%u) -> %d, %c\n", 0xC200+i, p, p);
    //}
    //cursor(1);
    //p = cgetc();
    //gotoxy(0, SIZE_Y-5);
    //printf("You said: %c\n", p);
}

unsigned char* write_string_to_ram(char* string_to_send, unsigned char address) {
	unsigned char i, p, c;
    unsigned char size = strlen(string_to_send);
    gotoxy(0,2);
    if (string_to_send[size-1] == '\n') {
        string_to_send[size-1] = 0;
    }
    //printf("write_string_to_ram()");
    for (i=0; i<size; i++) {
        write_data(address+i, string_to_send[i]);
    }
    if (string_to_send[size-1] != 0) {
        write_data(address+i, 0);
    }
    gotoxy(0,9);
    p = cgetc();
}

unsigned char* read_string_from_ram(char* string_to_send, unsigned char address) {
    gotoxy(0,2);
    printf("read_string_from_ram()");
}
