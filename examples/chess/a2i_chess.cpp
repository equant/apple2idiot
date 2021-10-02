#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Apple2Idiot.h>
//#include "chess_commands.h"
#include "a2i_chess.h"


void Chess::init(Apple2Idiot *a2ip, HTTPClient *httpp) {
    a2i  = a2ip;
    http = httpp;
    strcpy(game_string, "a2a3e7e5e2e4");
}

byte Chess::handleCommand(byte command) {
    switch(command) {
        case CHESS_MAKE_MOVE: {
            Serial.println("CHESS() MAKE_MOVE");
            a2i->write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            String move_string;
            move_string = a2i->read_string_from_ram(SHARED_RAM_START_ADDRESS);
            Serial.println("Received move: ["+move_string+"]");
            byte result = makeMove(move_string);
            return result;
            /*
            switch(result) {
                case CHESS_INVALID_MOVE: {
                    break;
                }
            }
            */
            break;
        }
        //case COMMAND_SET_CITY:
            //Serial.println("COMMAND_SET_CITY");
            //a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            //city_name = a2i.read_string_from_ram(SHARED_RAM_START_ADDRESS);
            //Serial.println("Received: ["+city_name+"]");
            //break;
        //case COMMAND_FETCH_WEATHER:
            //Serial.println("COMMAND_FETCH_WEATHER");
            //a2i.write_data(ESP_COMMAND_ADDRESS, ACK);      // notify Apple IIe we are processing command byte
            //result = fetch_weather();
            //break;
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
        char* ai_move;
        ai_move = getAIMove();
        strcat(game_string, ai_move);
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
    Serial.print("getGameStatus() "); Serial.println(game_status);

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/status/%s", api_entry_point, game_string);
    Serial.print("    "); Serial.println(api_request);
    http->begin(api_request);
    int httpCode = http->GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http->getString();
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
    Serial.print("getAIMove() "); Serial.println(game_status);

    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/next_best/%s", api_entry_point, game_string);
    Serial.print("    "); Serial.println(api_request);
    http->begin(api_request);
    int httpCode = http->GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http->getString();
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
    Serial.print("validateMove() "); Serial.println(move_string);
    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/valid_move/%s%s", api_entry_point, game_string, move_string);
    Serial.print("    "); Serial.println(api_request);
    http->begin(api_request);
    int httpCode = http->GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http->getString();
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
    Serial.println("getBoard() ");
    char api_request[MAX_STR_LEN];
    sprintf(api_request, "%s/board_string/%s", api_entry_point, game_string);
    Serial.print("    "); Serial.println(api_request);
    http->begin(api_request);
    int httpCode = http->GET();  //Make the request
    delay(10);
    if (httpCode > 0) { //Check for the returning code
        Serial.println("    Success on HTTP request");
        String payload = http->getString();
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
            while (pch != NULL) {
                char my_line[30];
                strcpy(my_line, pch);
                removeSubstr(my_line, "[37m");
                removeSubstr(my_line, "[0m");
                removeSubstr(my_line, "\n");
                Serial.print("        | "); Serial.print(my_line); Serial.println(" |");
                pch = strtok(NULL, "\n");
            }
            //return (char *)doc["bestNext"].as<char *>();
        }
    } else {
        Serial.println("Error on HTTP request");
    }
    // Don't know how we could get here without it being an error.
}
