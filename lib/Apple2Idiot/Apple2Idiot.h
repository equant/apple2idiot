#ifndef APPLE2IDIOT
#define APPLE2IDIOT
#include <Arduino.h>

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

//
// Commands and messages that are communicated between the ESP and the Apple
// via the dual-port ram.
//
// Commands >=200 are "non-reserved", and are meant
// to be defined within scipts that use this library.
// So anything in this library should be below 200.
//
// If the values of these defines are changed, then they will need to be
// updated within the code that runs on the Apple as well.

//#define COMMAND_GENERIC 0b10000000
#define COMMAND_WIFI_SCAN 111
#define COMMAND_WIFI_CONNECT 112
#define ACK 0b00000110  // Acknowledge
#define EOT 0b00000100  // End of transmit
#define ERR 0b00000101  // Error
#define MORE_TO_SEND 0b00000111

/* IDT7132S dual port ram chip enable */
#define RW_PIN      5
#define RW_WRITE    LOW
#define RW_READ     HIGH

#define ETX 3   // ASCII "End of Text" (ETX) character

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
