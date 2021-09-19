#ifndef _A2I_H
#define _A2I_H


unsigned char read_data(unsigned char address);
unsigned char write_data(unsigned char address, unsigned char byte_to_write);
unsigned char* write_string_to_ram(char* string_to_send, unsigned char address);
unsigned char* read_string_from_ram(char* string_to_send, unsigned char address);

#endif
