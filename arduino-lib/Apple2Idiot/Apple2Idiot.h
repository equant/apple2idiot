#ifndef APPLE2IDIOT_H
#define APPLE2IDIOT_H
#include <Arduino.h>
#include "A2I_commands.h"

/* DATA BUS (numbers mean GPIO port) */
#define D0R 12
#define D1R 13
#define D2R 14
#define D3R 15
#define D4R 16
#define D5R 17
#define D6R 18
#define D7R 19
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
#define ADDRESS_BUS_SIZE 8

#define ESP_COMMAND_ADDRESS 0
#define APPLE_COMMAND_ADDRESS 1
#define SHARED_RAM_START_ADDRESS 2
#define RAM_BUSY 666
#define MAX_STR_LEN 250    // arbitrary length.


/* IDT7132S dual port ram chip enable */
#define RW_PIN      5
#define RW_WRITE    LOW
#define RW_READ     HIGH

// Deprecated ETX.  Use NULL terminated strings now.
//#define ETX 0   // ASCII "End of Text" (ETX) character
#define EOS 0

#define INPUT_35 35
#define INPUT_34 34


class Apple2Idiot {

    private:
    void unbusy_ram();

    public:
    Apple2Idiot();
    void init();
    boolean set_address(int address);
    byte read_data(int address);
    boolean write_data(byte address, byte byte_to_write);
    unsigned int write_string_to_shared_ram(String string_to_send, unsigned int address);
    String read_string_from_ram(int address);
    void read_ram(int size_to_read=256);
};

#endif
