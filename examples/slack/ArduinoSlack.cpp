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

int ArduinoSlack::makeGetRequest(const char *command, const char *body, const char *contentType)
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

SlackConvoHist ArduinoSlack::conversationHistory(const char *channel, const char *limit)
{
    SLACK_DEBUG_SERIAL_LN(F("--------------"));
    SLACK_DEBUG_SERIAL_LN(F("conversationHistory()"));
    char body[300];
    sprintf(body, setConvoHistoryBody, channel, limit);
    SLACK_DEBUG_SERIAL_LN(body);

    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackConvoHist conversation;;
    // This flag will get cleared if all goes well
    conversation.error = true;
    if (makePostRequest(SLACK_CONVERSATIONS_HISTORY_ENDPOINT, body) == 200)
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
            JsonObject messageObj = doc["messages"];
            conversation.messageObj = messageObj;

            //message.text     = (char *)messageObj["text"].as<char *>();
            //message.username = (char *)messageObj["username"].as<char *>();
            //message.bot_id   = (char *)messageObj["bot_id"].as<char *>();
            //message.type     = (char *)messageObj["type"].as<char *>();

            conversation.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    }
    closeClient();
    return conversation;
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
            SLACK_DEBUG_SERIAL(F("Tossing an unexpected character: "));
            SLACK_DEBUG_SERIAL_LN(c);
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
