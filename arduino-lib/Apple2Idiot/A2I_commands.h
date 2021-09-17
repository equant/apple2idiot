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
