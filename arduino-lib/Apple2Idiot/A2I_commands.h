#ifndef A2I_COMMANDS_H
#define A2I_COMMANDS_H
//
// Addresses, Commands and messages that are communicated between the ESP and the Apple
// via the dual-port ram.


// Address offsets
#define RAM_A2I 0
#define RAM_APPLE 1 
#define SHARED_RAM_START_ADDRESS 2 


#define MAIN_LOOP_INTERVAL  3   // Unimplemented
#define EOT 4               // End of transmit
#define ERR 5               // Error
#define ACK 6               // Acknowledge

#define COMMAND_NOT_FOUND 7

/*################################################
#                GENERIC STATUSES                #
################################################*/
#define MORE_TO_SEND 10
#define NOT_FOUND 11

/*################################################
#                      WIFI                      #
################################################*/
#define COMMAND_WIFI_SCAN 21
#define COMMAND_WIFI_CONNECT 22
#define COMMAND_WIFI_DISCONNECT 23      // Unimplemented
#define WIFI_CONNECTED 24               // Unimplemented
#define WIFI_NOT_CONNECTED 25           // Unimplemented

/*################################################
#                  PROGRAM IDS                   #
################################################*/

#define APP_WEATHER 200                 // Unimplemented
#define APP_CHESS   201                 // Unimplemented


/*################################################
#                     SLACK (50)                 #
################################################*/
#define COMMAND_GET_N_CHANNELS 50   // Return number of channels
#define COMMAND_GET_CHANNEL_N 51    // Return info for channel identified by #n
#define COMMAND_GET_CHANNEL_STR 52    // Return info for channel identified by string (id or name)
#define COMMAND_SET_CHANNEL 53
#define COMMAND_SEND_MESSAGE 54
#define COMMAND_GET_MESSAGES 55

#endif
