#ifndef A2I_WEATHER_H
#define A2I_WEATHER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <A2I_commands.h>
#include <Apple2Idiot.h>
#include "weather_commands.h"
#include "credentials.h"

class Weather {

    public:
        // This is "registered" with A2I_commands.h which is part of Apple2Idiot.h This
        // id is sent from the Apple to the ESP to tell the esp what app is currently
        // active.  The main loop of the ESP sketch then knows to use this class to
        // respond to incoming commands from the Apple.
        byte appId = APP_WEATHER;

        String country_code = "US";
        String city_name = "Tucson";

        void init(Apple2Idiot *a2ip, HTTPClient *httpp);
        //char* getGameStatus(char* game_status);
        //byte makeMove(String move_string);
        byte handleCommand(byte command);
        byte fetch_weather();
        //byte validateMove(String move_string);
        //char* getAIMove();
        //void getBoard();

    private:

        Apple2Idiot *a2i;
        HTTPClient *http;

        void removeSubstr (char *string, char *sub);
        const char api_entry_point[49] = "http://api.openweathermap.org/data/2.5/weather?";
        /* Remember, flexible array won't work
         * in a class, so don't try to do this...
         *     const char foo[] = "hello world";
         */

};

#endif

