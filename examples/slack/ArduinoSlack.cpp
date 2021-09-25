/*
Copyright (c) 2020 Brian Lough. All right reserved.

ArduinoSlack - An Arduino library to wrap the Slack API

MIT License
*/

#include "ArduinoSlack.h"

ArduinoSlack::ArduinoSlack(Client &client, const char *bearerToken)
{
    this->client = &client;
    this->_bearerToken = bearerToken;
}

int ArduinoSlack::makeGetRequest(const char *command)
{
    client->flush();
    client->setTimeout(SLACK_TIMEOUT);
    if (!client->connect(SLACK_HOST, portNumber))
    {
        SLACK_SERIAL_LN(F("Connection failed"));
        return false;
    }

    // give the esp a breather
    yield();

    // Send HTTP request
    client->print(F("GET "));
    client->print(command);
    client->println(F(" HTTP/1.1"));

    //Headers
    client->print(F("Host: "));
    client->println(SLACK_HOST);

    //client->println(F("Accept: application/json"));
    //client->print(F("Content-Type: "));
    //client->println(contentType);

    client->print(F("Authorization: Bearer "));
    client->println(_bearerToken);

    client->println(F("Cache-Control: no-cache"));

    //client->print(F("Content-Length: "));
    //client->println(strlen(body));

    client->println();
    //client->println();

    //send Data here?
    //client->print(body);

    if (client->println() == 0)
    {
        SLACK_SERIAL_LN(F("Failed to send request"));
        return false;
    }

    int statusCode = getHttpStatusCode();
    skipHeaders();
    return statusCode;
}


int ArduinoSlack::makePostRequest(const char *command, const char *body, const char *contentType)
{
    client->flush();
    client->setTimeout(SLACK_TIMEOUT);
    if (!client->connect(SLACK_HOST, portNumber))
    {
        SLACK_SERIAL_LN(F("Connection failed"));
        return false;
    }

    // give the esp a breather
    yield();

    // Send HTTP request
    client->print(F("POST "));
    client->print(command);
    client->println(F(" HTTP/1.1"));

    //Headers
    client->print(F("Host: "));
    client->println(SLACK_HOST);

    client->println(F("Accept: application/json"));
    client->print(F("Content-Type: "));
    client->println(contentType);

    client->print(F("Authorization: Bearer "));
    client->println(_bearerToken);

    client->println(F("Cache-Control: no-cache"));

    client->print(F("Content-Length: "));
    client->println(strlen(body));

    client->println();

    //send Data here?
    client->print(body);

    if (client->println() == 0)
    {
        SLACK_SERIAL_LN(F("Failed to send request"));
        return false;
    }

    int statusCode = getHttpStatusCode();
    skipHeaders();
    return statusCode;
}

bool ArduinoSlack::setPresence(const char *presence)
{
    char command[100];
    sprintf(command, SLACK_USERS_SET_PRESENCE_ENDPOINT, presence);
    SLACK_DEBUG_SERIAL_LN(command);

    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = 1000;
    bool okStatus = false;
    if (makePostRequest(command, "", "text/plain") == 200)
    {
        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        DeserializationError error = deserializeJson(doc, *client);
        if (!error)
        {
            SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
#ifdef SLACK_ENABLE_DEBUG
            serializeJson(doc, Serial);
#endif
            okStatus = doc["ok"];
            if (!okStatus)
            {
                if (doc.containsKey("error"))
                {
                    const char *errorMsg = doc["error"];
                    SLACK_DEBUG_SERIAL(F("Got the following error: "));
                    SLACK_DEBUG_SERIAL_LN(errorMsg);
                }
                else
                {
                    SLACK_DEBUG_SERIAL_LN(F("Unkown Error"));
                }
            }
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    }
    closeClient();
    return okStatus;
}

SlackUsersConversations ArduinoSlack::usersConversations()
{
    //char body[300];
    //sprintf(body, setConvoHistoryBody, channel, limit);
    //SLACK_DEBUG_SERIAL_LN(body);

    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackUsersConversations conversations;
    // This flag will get cleared if all goes well
    conversations.error = true;
    //SLACK_SERIAL_LN("GET String:");
    //SLACK_SERIAL_LN(SLACK_CONVERSATIONS_HISTORY_ENDPOINT);
    //SLACK_SERIAL_LN(usersConversationsGET);
    //int response = makeGetRequest(SLACK_USERS_CONVERSATIONS_ENDPOINT);
    int response = makeGetRequest("/api/users.conversations?exclude_arc=True&limit=17");
    //if (makeGetRequest(SLACK_USERS_CONVERSATIONS_ENDPOINT) == 200)
    if (response == 200)
    {

        // So it seems for whatever reason every other line is bad.  I don't
        // know why this is, but this will remove them so they don't break
        // the Json...
        String chunk;
        String payload;
        int limit=1;
        do {
            if (client->connected()) {
              yield();
              chunk = client->readStringUntil('\n');
              //SLACK_DEBUG_SERIAL("CHUNK #");
              //SLACK_DEBUG_SERIAL(limit);
              //SLACK_DEBUG_SERIAL(": ");
              //SLACK_DEBUG_SERIAL_LN(chunk);
              if (limit % 2 == 0) {
                  // skip even lines.
              } else {
                  payload += chunk;
              }
            }
        } while (chunk.length() > 0 && ++limit < 100);
        //String payload = client->readString();
        //SLACK_DEBUG_SERIAL_LN("Payload!");
        //SLACK_DEBUG_SERIAL_LN(payload);

        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        StaticJsonDocument<200> filter;
        filter["channels"][0]["name"]   = true;
        filter["channels"][0]["id"]   = true;
        filter["response_metadata"]["next_cursor"] = true;
        //StaticJsonDocument<400> doc;
        //DeserializationError error = deserializeJson(doc, *client, DeserializationOption::Filter(filter));
        DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        if (!error)
        {
            SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
#ifdef SLACK_ENABLE_DEBUG
            serializeJson(doc, Serial);
#endif

            JsonObject channelsObj = doc["channels"];
            conversations.channelsObj = channelsObj;
            SLACK_DEBUG_SERIAL_LN(F(""));
            SLACK_DEBUG_SERIAL_LN(F("+++++++++++++++++++++++++++++++++"));
            SLACK_DEBUG_SERIAL_LN(doc["channels"].size());
            SLACK_DEBUG_SERIAL_LN(F(""));
            serializeJsonPretty(doc["channels"][0], Serial);
            SLACK_DEBUG_SERIAL_LN(F(""));
            serializeJsonPretty(doc["channels"][1], Serial);
            SLACK_DEBUG_SERIAL_LN(F(""));
            serializeJsonPretty(doc["channels"][doc["channels"].size()-1], Serial);
            SLACK_DEBUG_SERIAL_LN(F(""));
            SLACK_DEBUG_SERIAL_LN(F("+++++++++++++++++++++++++++++++++"));
            SLACK_DEBUG_SERIAL_LN(F(""));

            //char (*a[2])[14]
            //String *channel_names[doc["channels"].size()];
            //String *channel_ids[doc["channels"].size()];
            //String channel_names[22];
            //String channel_ids[22];
            for (int ii=0; ii<doc["channels"].size(); ii++) {
                //channel_names[ii] = (char *)doc["channels"][ii]["name"].as<char *>();
                //channel_ids[ii]   = (char *)doc["channels"][ii]["id"].as<char *>();
                //channel_names[ii] = doc["channels"][ii]["name"];
                //channel_ids[ii]   = doc["channels"][ii]["id"];
                //conversations.channelNames[ii] = doc["channels"][ii]["name"];
                conversations.channelNames[ii] = (char *)doc["channels"][ii]["name"].as<char *>();
            }

            //conversations.channelNames = (char *)doc[0]["name"].as<char *>();
            //conversations.channelIds   = (char *)doc[0]["id"].as<char *>();
            //channels.text     = (char *)doc["text"].as<char *>();
            //channels.username = (char *)doc["username"].as<char *>();
            //channels.bot_id   = (char *)doc["bot_id"].as<char *>();
            //channels.type     = (char *)doc["type"].as<char *>();

            //channels.channelNames = channel_names;
            //channels.channelIds = channel_ids;


            conversations.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    } else {
        SLACK_DEBUG_SERIAL_LN(F("Didn't get 200"));
            SLACK_DEBUG_SERIAL_LN(response);
    }
    closeClient();
    return conversations;
}


SlackMessage ArduinoSlack::postMessage(const char *channel, const char *text)
{
    char body[300];
    sprintf(body, setMessageBody, channel, text);
    SLACK_DEBUG_SERIAL_LN(body);

    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackMessage message;
    // This flag will get cleared if all goes well
    message.error = true;
    if (makePostRequest(SLACK_POST_MESSAGE_ENDPOINT, body) == 200)
    {
        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        DeserializationError error = deserializeJson(doc, *client);
        if (!error)
        {
            SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
#ifdef SLACK_ENABLE_DEBUG
            serializeJson(doc, Serial);
#endif
            JsonObject messageObj = doc["message"];

            message.text     = (char *)messageObj["text"].as<char *>();
            message.username = (char *)messageObj["username"].as<char *>();
            message.bot_id   = (char *)messageObj["bot_id"].as<char *>();
            message.type     = (char *)messageObj["type"].as<char *>();

            message.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    }
    closeClient();
    return message;
}

SlackProfile ArduinoSlack::setCustomStatus(const char *text, const char *emoji, int expiration)
{
    SLACK_DEBUG_SERIAL_LN(F("setCustomStatus()"));
    char body[300];
    sprintf(body, setEndpointBody, text, emoji, expiration);
    SLACK_DEBUG_SERIAL_LN(body);

    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackProfile profile;
    // This flag will get cleared if all goes well
    profile.error = true;
    if (makePostRequest(SLACK_USERS_PROFILE_SET_ENDPOINT, body) == 200)
    {
        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        DeserializationError error = deserializeJson(doc, *client);
        if (!error)
        {
            SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
#ifdef SLACK_ENABLE_DEBUG
            serializeJson(doc, Serial);
#endif
            JsonObject profileObj = doc["profile"];

            profile.displayName = (char *)profileObj["display_name"].as<char *>();
            profile.statusText = (char *)profileObj["status_text"].as<char *>();
            profile.statusEmoji = (char *)profileObj["status_emoji"].as<char *>();

            profile.statusExpiration = profileObj["status_expiration"].as<int>();

            profile.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    }
    closeClient();
    return profile;
}

void ArduinoSlack::skipHeaders(bool tossUnexpectedForJSON)
{
    // Skip HTTP headers
    if (!client->find("\r\n\r\n"))
    {
        SLACK_SERIAL_LN(F("Invalid response"));
        return;
    }

    if (tossUnexpectedForJSON)
    {
        // Was getting stray characters between the headers and the body
        // This should toss them away
        while (client->available() && client->peek() != '{')
        {
            char c = 0;
            client->readBytes(&c, 1);
            //SLACK_DEBUG_SERIAL(F("Tossing an unexpected character: "));
            //SLACK_DEBUG_SERIAL_LN(c);
        }
    }
}

int ArduinoSlack::getHttpStatusCode()
{
    // Check HTTP status
    if (client->find("HTTP/1.1"))
    {
        int statusCode = client->parseInt();
        SLACK_DEBUG_SERIAL(F("Status Code: "));
        SLACK_DEBUG_SERIAL_LN(statusCode);
        return statusCode;
    }

    return -1;
}

void ArduinoSlack::closeClient()
{
    if (client->connected())
    {

        SLACK_DEBUG_SERIAL_LN(F("Closing client"));
        client->stop();
    }
}
