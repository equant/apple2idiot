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

#define SHARED_RAM_START_ADDRESS 2

#define ACK 0b00000110  // Acknowledge
#define EOT 0b00000100  // End of transmit
#define ERR 0b00000101  // Error
#define MORE_TO_SEND 0b00000111

/*################################################
#                GENERIC STATUSES                #
################################################*/
#define NOT_FOUND 11

/*################################################
#                      WIFI                      #
################################################*/
#define COMMAND_WIFI_SCAN 111
#define COMMAND_WIFI_CONNECT 112

/*################################################
#                     SLACK (50)                 #
################################################*/
#define COMMAND_GET_N_CHANNELS 50   // Return number of channels
#define COMMAND_GET_CHANNEL_N 51    // Return info for channel identified by #n
#define COMMAND_GET_CHANNEL_STR 52    // Return info for channel identified by string (id or name)
#define COMMAND_SET_CHANNEL 53
#define COMMAND_SEND_MESSAGE 54
#define COMMAND_GET_MESSAGES 55

