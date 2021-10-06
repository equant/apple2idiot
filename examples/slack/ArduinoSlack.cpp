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
    Serial.println("ArduinoSlack::makeGetRequest()");
    client->flush();
    client->setTimeout(SLACK_TIMEOUT);
    if (!client->connect(SLACK_HOST, portNumber))
    {
        SLACK_SERIAL_LN(F("    Connection failed"));
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
        SLACK_SERIAL_LN(F("    Failed to send request"));
        return false;
    }

    int statusCode = getHttpStatusCode();
    skipHeaders();
    return statusCode;
}


int ArduinoSlack::makePostRequest(const char *command, const char *body, const char *contentType)
{
    Serial.println("ArduinoSlack::makePostRequest()");
    client->flush();
    client->setTimeout(SLACK_TIMEOUT);
    if (!client->connect(SLACK_HOST, portNumber))
    {
        SLACK_SERIAL_LN(F("    Connection failed"));
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
            //SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
            //serializeJson(doc, Serial);

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
    Serial.println("ArduinoSlack::usersConversations()");
    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackUsersConversations conversations;
    // This flag will get cleared if all goes well
    conversations.error = true;

    int response = makeGetRequest("/api/users.conversations?exclude_arc=True&limit=5");

    if (response == 200)
    {
        //String payload = client->readString();
        //String payload = stripBadDataFromClientResponse();
        char payload[8000];
        stripBadDataFromClientResponse(payload);

        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        StaticJsonDocument<200> filter;
        filter["channels"][0]["name"]              = true;
        filter["channels"][0]["id"]                = true;
        filter["channels"][0]["is_channel"]        = true;
        filter["channels"][0]["topic"]["value"]    = true;
        filter["channels"][0]["purpose"]["value"]  = true;
        filter["response_metadata"]["next_cursor"] = true;
        DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        if (!error)
        {
            //SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
            //serializeJson(doc, Serial);

            JsonObject channelsObj = doc["channels"];
            conversations.channelsObj = channelsObj;

            for (int i=0; i<doc["channels"].size(); i++) {
                conversations.channelNames[i] = (char *)doc["channels"][i]["name"].as<char *>();
                conversations.channelIds[i]   = (char *)doc["channels"][i]["id"].as<char *>();
                conversations.purpose[i]      = (char *)doc["channels"][i]["purpose"]["value"].as<char *>();
                conversations.topic[i]        = (char *)doc["channels"][i]["topic"]["value"].as<char *>();
                conversations.n_channels      = doc["channels"].size();
            }

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


SlackMessages ArduinoSlack::channelHistory(char *channelId) {
    Serial.println("ArduinoSlack::channelHistory()");
    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackMessages history;
    // This flag will get cleared if all goes well
    history.error = true;

    char endpoint[100];
    sprintf(endpoint, getConvHistEndpointArgs, channelId, 20);
    Serial.print("    channelId:");
    Serial.println(channelId);
    Serial.print("    ENDPOINT: ");
    Serial.println(endpoint);

    //int response = makeGetRequest("/api/conversations.history?channel="+channelId+"&limit=20");
    //int response = makeGetRequest("/api/conversations.history?channel=C02EAQECY5A&limit=20");
    //SLACK_DEBUG_SERIAL(F("GET: "));
    //SLACK_DEBUG_SERIAL_LN(F(endpoint));
    int response = makeGetRequest(endpoint);

    if (response == 200)
    {
        //String payload = client->readString();
        //String payload = stripBadDataFromClientResponse();
        char payload[8000];
        stripBadDataFromClientResponse(payload);

        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        StaticJsonDocument<200> filter;
        filter["ok"]                                   = true;
        filter["messages"][0]["text"]                  = true;
        filter["messages"][0]["user"]                  = true;
        filter["messages"][0]["reactions"][0]["name"]  = true;
        filter["messages"][0]["reactions"][0]["users"] = true;
        filter["messages"][0]["reactions"][0]["count"] = true;
        filter["response_metadata"]["next_cursor"]     = true;
        DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        if (!error)
        {
            //SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
            //serializeJson(doc, Serial);

            SLACK_DEBUG_SERIAL_LN(F(""));
            SLACK_DEBUG_SERIAL_LN(F("+++++++++++++++++++++++++++++++++"));
            //SLACK_DEBUG_SERIAL_LN(doc["channels"].size());
            serializeJsonPretty(doc["messages"][0], Serial);
            SLACK_DEBUG_SERIAL_LN(F(""));
            SLACK_DEBUG_SERIAL_LN(F("+++++++++++++++++++++++++++++++++"));
            SLACK_DEBUG_SERIAL_LN(F(""));

            for (int i=0; i<doc["channels"].size(); i++) {
                history.messages[i].text     = (char *)doc["messages"][i]["text"].as<char *>();
                //history.messages[i].userid   = (char *)doc["messages"][i]["user"].as<char *>();
                //history.messages[i].username = "unknown";
                //history.messages[i].type     = (char *)doc["messages"][i]["type"].as<char *>();
                //history.n_messages      = doc["messages"].size();
            }

            history.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("    deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    } else {
        SLACK_DEBUG_SERIAL_LN(F("    Didn't get 200"));
            SLACK_DEBUG_SERIAL_LN(response);
    }
    closeClient();
    return history;
}


SlackMessage ArduinoSlack::postMessage(const char *channel, const char *text) {
    Serial.println("ArduinoSlack::postMessage()");
    char body[300];
    sprintf(body, setMessageBody, channel, text);
    Serial.print("    "); Serial.println(body);

    // Get from https://arduinojson.org/v6/assistant/
    const size_t bufferSize = profileBufferSize;

    SlackMessage message;
    // This flag will get cleared if all goes well
    message.error = true;
    Serial.print("    B4 Post:"); Serial.println(channel);
    if (makePostRequest(SLACK_POST_MESSAGE_ENDPOINT, body) == 200) {
        Serial.print("    AR Post:"); Serial.println(channel);
        // Allocate DynamicJsonDocument
        DynamicJsonDocument doc(bufferSize);

        // Parse JSON object
        DeserializationError error = deserializeJson(doc, *client);
        if (!error)
        {
            //SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
            //serializeJson(doc, Serial);
            //JsonObject messageObj = doc["message"];
            //message.text     = (char *)messageObj["text"].as<char *>();
            //message.username = (char *)messageObj["username"].as<char *>();
            //message.bot_id   = (char *)messageObj["bot_id"].as<char *>();
            //message.type     = (char *)messageObj["type"].as<char *>();
            message.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("    deserializeJson() failed with code "));
            SLACK_DEBUG_SERIAL_LN(error.c_str());
        }
    }
    Serial.print("    BR closeClient:"); Serial.println(channel);
    closeClient();
    Serial.print("    AR closeClient:"); Serial.println(channel);
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
            //SLACK_DEBUG_SERIAL_LN(F("parsed Json Object: "));
            //serializeJson(doc, Serial);

            JsonObject profileObj = doc["profile"];

            profile.displayName = (char *)profileObj["display_name"].as<char *>();
            profile.statusText = (char *)profileObj["status_text"].as<char *>();
            profile.statusEmoji = (char *)profileObj["status_emoji"].as<char *>();

            profile.statusExpiration = profileObj["status_expiration"].as<int>();

            profile.error = false;
        }
        else
        {
            SLACK_DEBUG_SERIAL(F("    deserializeJson() failed with code "));
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
        SLACK_DEBUG_SERIAL(F("    Status Code: "));
        SLACK_DEBUG_SERIAL_LN(statusCode);
        return statusCode;
    }

    return -1;
}

void ArduinoSlack::closeClient()
{
    if (client->connected())
    {

        //SLACK_DEBUG_SERIAL_LN(F("Closing client"));
        client->stop();
    }
}



void ArduinoSlack::stripBadDataFromClientResponse(char *payload) {
    // So it seems for whatever reason every other line is bad.  I don't
    // know why this is, but this will remove them so they don't break
    // the Json...
    String chunk;
    int count=1;
    //SLACK_DEBUG_SERIAL_LN("PAYLOAD:");
    do {
        if (client->connected()) {
          yield();
          chunk = client->readStringUntil('\n');
          chunk.remove(-1,1); // Get rid of trailing \n which can often bork things.
          if (count % 2 == 0) {
              // skip even lines.
              //SLACK_DEBUG_SERIAL("SKIP Line #");
              //SLACK_DEBUG_SERIAL(limit);
              //SLACK_DEBUG_SERIAL(": ");
              //SLACK_DEBUG_SERIAL_LN(chunk);
          } else {
              //SLACK_DEBUG_SERIAL("KEEP Line #");
              //SLACK_DEBUG_SERIAL(limit);
              //SLACK_DEBUG_SERIAL(": ");
              //SLACK_DEBUG_SERIAL(chunk);
              //payload += chunk;
              strcat(payload, chunk.c_str());
          }
        }
    } while (chunk.length() > 0 && ++count < 100);
    SLACK_DEBUG_SERIAL_LN(payload);
    SLACK_DEBUG_SERIAL_LN("");
    //return payload;
}
