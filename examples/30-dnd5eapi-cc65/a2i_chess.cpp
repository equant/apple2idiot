#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Apple2Idiot.h>
#include "chess_commands.h"
#include "a2i_chess.h"


void Chess::init(Apple2Idiot *a2ip, HTTPClient *httpp) {
    a2i  = a2ip;
    http = httpp;
    //strcpy(game_string, "a2a3e7e5e2e4");
}

byte Chess::handleCommand(byte command) {
    switch(command) {
        case CHESS_MAKE_MOVE: {
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            Serial.println("CHESS() MAKE_MOVE");
            String move_string;
            move_string = a2i->read_string_from_ram(SHARED_RAM_START_ADDRESS);
            Serial.println("Received move: ["+move_string+"]");
            byte result = makeMove(move_string);
            int address_counter = a2i->write_string_to_shared_ram(last_ai_move, SHARED_RAM_START_ADDRESS);
            getBoard();
            for (int i=0; i<9; i++) {
                address_counter = a2i->write_string_to_shared_ram(game_board[i], address_counter + 1);
            }
            a2i->write_data(ESP_COMMAND_ADDRESS, result);
            a2i->read_ram(11);
            return ACK;
        }
        case CHESS_NEW_GAME: {
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            Serial.println("CHESS_NEW_GAME");
            strcpy(game_string, "");
            return ACK;
        }
        default: {
            return COMMAND_NOT_FOUND;
        }
    }
}

byte Chess::makeMove(String move_string) {
    /* Apple says MAKE_MOVE and sends "a2a3"
     * 
     * The basic flow...
     *
     * validateMove()   We check that it's valid.
     *                  If it is we accept the move and add it to game_string
     * getGameStatus()  Then we check the status and return (did someone win or lose?)
     * getAIMove()      Then we get the AI move.
     *                  Then we check the status and return (did someone win or lose?)
     */
    Apple2Idiot a2i;
    HTTPClient http;
    if (validateMove(move_string) == CHESS_VALID_MOVE) {
        strcat(game_string, move_string.c_str());
    } else {
        return CHESS_INVALID_MOVE;
    }
    char* game_status;
    //b = getGameStatus(game_string);
    game_status = getGameStatus(game_string);
    Serial.print("after player move game_status:"); Serial.println(game_status);

    if (strcmp(game_status, "in_progress") == 0) {
        //char* ai_move;
        //ai_move = getAIMove();
        //strcat(game_string, ai_move);
        //last_ai_move = getAIMove();
        strcpy(last_ai_move, getAIMove());
        strcat(game_string, last_ai_move);
        game_status = getGameStatus(game_string);
        Serial.print("after AI move game_status:"); Serial.println(game_status);
        if (strcmp(game_status, "in_progress") == 0) { return STATUS_IN_PROGRESS; }
        else if (strcmp(game_status, "black_won") == 0) { return STATUS_BLACK_WON; }
        else if (strcmp(game_status, "white_won") == 0) { return STATUS_WHITE_WON; }
        else if (strcmp(game_status, "white_won_resign") == 0) { return STATUS_UNHANDLED; }
        else if (strcmp(game_status, "black_won_resign") == 0) { return STATUS_UNHANDLED; }
        else if (strcmp(game_status, "stalemate") == 0) { return STATUS_STALEMATE; }
        else if (strcmp(game_status, "insufficient_material") == 0) { return STATUS_UNHANDLED; }
        else if (strcmp(game_status, "fifty_rule_move") == 0) { return STATUS_FIFTY_RULE_MOVE; }
        else if (strcmp(game_status, "threefold_repitition") == 0) { return STATUS_UNHANDLED; }
        else if (strcmp(game_status, "unknown") == 0) { return STATUS_UNKNOWN; } else { return STATUS_ERROR; }
    }
    else if (strcmp(game_status, "black_won") == 0) { return STATUS_BLACK_WON; }
    else if (strcmp(game_status, "white_won") == 0) { return STATUS_WHITE_WON; }
    else if (strcmp(game_status, "white_won_resign") == 0) { return STATUS_UNHANDLED; }
    else if (strcmp(game_status, "black_won_resign") == 0) { return STATUS_UNHANDLED; }
    else if (strcmp(game_status, "stalemate") == 0) { return STATUS_STALEMATE; }
    else if (strcmp(game_status, "insufficient_material") == 0) { return STATUS_UNHANDLED; }
    else if (strcmp(game_status, "fifty_rule_move") == 0) { return STATUS_FIFTY_RULE_MOVE; }
    else if (strcmp(game_status, "threefold_repitition") == 0) { return STATUS_UNHANDLED; }
    else if (strcmp(game_status, "unknown") == 0) { return STATUS_UNKNOWN; } else { return STATUS_ERROR; }
}

char* Chess::getGameStatus(char* game_string) {
    Apple2Idiot a2i;
    HTTPClient http;
    Serial.print("getGameStatus() "); Serial.println(game_status);

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/status/%s", api_entry_point, game_string);
    Serial.print("    "); Serial.println(api_request);
    http.begin(api_request);
    int httpCode = http.GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http.getString();
        //Serial.println("++++++++++++++++++++++++");
        //Serial.println(payload);
        //Serial.println("++++++++++++++++++++++++");
        StaticJsonDocument<400> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("    deserializeJson() failed: "));
            Serial.println(error.f_str());
            return "error";
        } else {
            Serial.println("----------------------");
            serializeJsonPretty(doc, Serial);
            Serial.println();
            Serial.println("----------------------");
            //return doc["gameStatus"];
            return (char *)doc["gameStatus"].as<char *>();
        }
    } else {
        Serial.println("Error on HTTP request");
        return "error";
    }
    // Don't know how we could get here without it being an error.

    return "error";
}

char* Chess::getAIMove() {
    Apple2Idiot a2i;
    HTTPClient http;
    Serial.print("getAIMove() "); Serial.println(game_status);

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/next_best/%s", api_entry_point, game_string);
    Serial.print("    "); Serial.println(api_request);
    http.begin(api_request);
    int httpCode = http.GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http.getString();
        //Serial.println("++++++++++++++++++++++++");
        //Serial.println(payload);
        //Serial.println("++++++++++++++++++++++++");
        StaticJsonDocument<400> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("    deserializeJson() failed: "));
            Serial.println(error.f_str());
            return "jsonerror";
        } else {
            Serial.println("----------------------");
            serializeJsonPretty(doc, Serial);
            Serial.println();
            Serial.println("----------------------");
            //return doc["gameStatus"];
            return (char *)doc["bestNext"].as<char *>();
        }
    } else {
        Serial.println("Error on HTTP request");
        return "geterror";
    }
    // Don't know how we could get here without it being an error.

    return "unknownerror";
}

byte Chess::validateMove(String move_string) {
    Apple2Idiot a2i;
    HTTPClient http;
    Serial.print("validateMove() "); Serial.println(move_string);
    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/valid_move/%s%s", api_entry_point, game_string, move_string);
    Serial.print("    "); Serial.println(api_request);
    http.begin(api_request);
    int httpCode = http.GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http.getString();
        //Serial.println("++++++++++++++++++++++++");
        //Serial.println(payload);
        //Serial.println("++++++++++++++++++++++++");
        StaticJsonDocument<400> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return ERR;
        } else {
            Serial.println("----------------------");
            serializeJsonPretty(doc, Serial);
            Serial.println();
            Serial.println("----------------------");
            bool validMove = doc["validMove"];
            if (validMove) {
                // good move
                Serial.println("    Valid move!");
                return CHESS_VALID_MOVE;
            } else {
                Serial.println("    Invalid move!");
                return CHESS_INVALID_MOVE;
            }
        }
    } else {
        Serial.println("Error on HTTP request");
        return ERR;
    }
    // Don't know how we could get here without it being an error.
    return ERR;
}

void Chess::removeSubstr (char *string, char *sub) {
    char *match = string;
    int len = strlen(sub);
    while ((match = strstr(match, sub))) {
        *match = '\0';
        strcat(string, match+len);
        match++;
    }
}

void Chess::getBoard() {
    Apple2Idiot a2i;
    HTTPClient http;
    Serial.println("getBoard() ");
    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/board_string/%s", api_entry_point, game_string);
    Serial.print("    "); Serial.println(api_request);
    http.begin(api_request);
    int httpCode = http.GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http.getString();
        //Serial.println("++++++++++++++++++++++++");
        //Serial.println(payload);
        //Serial.println("++++++++++++++++++++++++");
        StaticJsonDocument<400> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        } else {
            //Serial.println("----------------------");
            //serializeJsonPretty(doc, Serial);
            //Serial.println();
            //Serial.println("----------------------");
            //Serial.println("    Break up the board...");
            //Serial.print("    BOARD:"); Serial.println((char *)doc["board"].as<char *>());
            char* pch = NULL;
            pch = strtok((char *)doc["board"].as<char *>(), "\n");
            //Serial.print("    pch:");Serial.println(pch);
            int row_count = 0;
            while (pch != NULL) {
                char board_line[30];
                strcpy(board_line, pch);
                removeSubstr(board_line, "[37m");
                removeSubstr(board_line, "[0m");
                removeSubstr(board_line, "\n");
                removeSubstr(board_line, "\e"); // remove escape (ASCII 27)
                removeSubstr(board_line, "\e"); // remove escape (ASCII 27)
                //Serial.print("(");Serial.print(row_count);Serial.print(")");
                //Serial.print(board_line); Serial.println("|");
                strcpy(game_board[row_count], board_line); // valid
                pch = strtok(NULL, "\n");
                row_count++;
            }
            Serial.println();
            for (int i=0; i<9; i++) {
                Serial.print("[");Serial.print(game_board[i]);Serial.println("]");
            }
        }
    } else {
        Serial.println("Error on HTTP request");
    }
    // Don't know how we could get here without it being an error.
}
