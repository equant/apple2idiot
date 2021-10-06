#ifndef _A2I_H
#define _A2I_H

unsigned char read_byte(unsigned int address);
unsigned char write_byte(unsigned int address, unsigned char byte_to_write);
unsigned char* write_string_to_ram(unsigned int address, char* string_to_send);
void read_string_from_ram(unsigned int address, char *data, char length);

#endif
