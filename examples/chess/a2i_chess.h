#ifndef A2I_CHESS_H
#define A2I_CHESS_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <A2I_commands.h>
#include <Apple2Idiot.h>
#include "chess_commands.h"


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

        //char game_board[9][20];
        char game_board[9][22] = {
            "8 r n b q k b n r",
            "7 p p p p p p p p",
            "6 . . . . . . . .",
            "5 . . . . . . . .",
            "4 . . . . . . . .",
            "3 . . . . . . . .",
            "2 P P P P P P P P",
            "1 R N B Q K B N R",
            "  a b c d e f g h"
        };

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

