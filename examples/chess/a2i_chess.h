#ifndef A2I_CHESS_H
#define A2I_CHESS_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <A2I_commands.h>
#include <Apple2Idiot.h>
//#include "chess_commands.h"

/* Apple II <-> ESP Commands */
#define CHESS_GET_AI_MOVE     20
#define CHESS_GET_GAME_STATUS 22
#define CHESS_GET_BOARD       23
#define CHESS_MAKE_MOVE       21

/* Responses */
#define CHESS_INVALID_MOVE    123
#define CHESS_VALID_MOVE      124

/*
 * Responses from API...
 * "in_progress"
 * "black_won"
 * "white_won"
 * "white_won_resign"
 * "black_won_resign"
 * "stalemate"
 * "insufficient_material"
 * "fifty_rule_move"
 * "threefold_repitition"
 * "unknown"
 */

#define STATUS_IN_PROGRESS 200
#define STATUS_BLACK_WON 201
#define STATUS_WHITE_WON 202
#define STATUS_STALEMATE 205
#define STATUS_FIFTY_RULE_MOVE 207
#define STATUS_UNKNOWN 209
#define STATUS_UNHANDLED 210
#define STATUS_ERROR 211

#define MAX_GAME_SIZE 110 * 4       // This is probably not enough, but it's fine for development.
                                    // https://chess.stackexchange.com/questions/2506/what-is-the-average-length-of-a-game-of-chess
                                    // times four because one move is "e7e5"

class Chess {

    public:
        byte appId = APP_CHESS;     // This is "registered" with A2I_commands.h which is part of Apple2Idiot.h
                                    // This id is sent from the Apple to the ESP to tell the esp what app
                                    // is currently active.  The main loop of the ESP sketch then knows to use
                                    // this class to respond to incoming commands from the Apple.


        char game_string[MAX_GAME_SIZE];    // This is probably not enough, but it's fine for development.

        char game_status[25];

        void init(Apple2Idiot *a2ip, HTTPClient *httpp);
        char* getGameStatus(char* game_status);
        byte makeMove(String move_string);
        byte handleCommand(byte command);
        byte validateMove(String move_string);
        char* getAIMove();
        void getBoard();

    private:

        Apple2Idiot *a2i;
        HTTPClient *http;

        void removeSubstr (char *string, char *sub);
        const char api_entry_point[32] = "http://chess-api.herokuapp.com";
        /* Remember, flexible array won't work
         * in a class, so don't try to do this...
         *     const char foo[] = "hello world";
         */

};

#endif

