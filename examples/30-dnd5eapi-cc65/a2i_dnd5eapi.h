
#ifndef A2I_DND5EAPI_H
#define A2I_DND5EAPI_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <A2I_commands.h>
#include <Apple2Idiot.h>
#include "dnd5eapi_commands.h"

class Dnd5eapi {

    public:
        // This is "registered" with A2I_commands.h which is part of Apple2Idiot.h This
        // id is sent from the Apple to the ESP to tell the esp what app is currently
        // active.  The main loop of the ESP sketch then knows to use this class to
        // respond to incoming commands from the Apple.
        byte appId = APP_DND5EAPI;

        String monster_search_string = "crab";

        void init(Apple2Idiot *a2ip, HTTPClient *httpp);
        byte handleCommand(byte command);
        byte searchMonster(byte command);
        byte fetch_dnd5eapi();

    private:

        Apple2Idiot *a2i;
        HTTPClient *http;

        void removeSubstr (char *string, char *sub);
        const char api_entry_point[49] = "https://www.dnd5eapi.co/api/";
        /* Remember, flexible array won't work
         * in a class, so don't try to do this...
         *     const char foo[] = "hello world";
         */

};

#endif

