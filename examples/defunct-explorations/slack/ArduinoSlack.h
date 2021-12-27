/*
Copyright (c) 2020 Brian Lough. All right reserved.

ArduinoSlack - An Arduino library to wrap the Slack API

MIT License
*/

#ifndef ArduinoSlack_h
#define ArduinoSlack_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>

#define SLACK_ENABLE_SERIAL

//un-mark following line to enable debug mode
#define SLACK_ENABLE_DEBUG

#ifdef SLACK_ENABLE_SERIAL
#define SLACK_SERIAL(STR) Serial.print(STR)
#define SLACK_SERIAL_LN(STR) Serial.println(STR)
#else
#define SLACK_SERIAL(STR)
#define SLACK_SERIAL_LN(STR)
#endif

#ifdef SLACK_ENABLE_DEBUG
#define SLACK_DEBUG_SERIAL(STR) Serial.print(STR)
#define SLACK_DEBUG_SERIAL_LN(STR) Serial.println(STR)
#else
#define SLACK_DEBUG_SERIAL(STR)
#define SLACK_DEBUG_SERIAL_LN(STR)
#endif

#define SLACK_HOST "slack.com"
// Fingerprint valid from Tue, 13 Apr 2021 00:00:00 GMT
#define SLACK_FINGERPRINT "C3 CC ED 77 87 19 6D E7 76 5E AA A7 3D 67 7E CA 95 D2 46 E2"
#define SLACK_TIMEOUT 2000

#define SLACK_PRESENCE_AWAY "away"
#define SLACK_PRESENCE_AUTO "auto"

#define SLACK_USERS_PROFILE_SET_ENDPOINT "/api/users.profile.set"
#define SLACK_USERS_SET_PRESENCE_ENDPOINT "/api/users.setPresence?presence=%s"
#define SLACK_POST_MESSAGE_ENDPOINT "/api/chat.postMessage"
#define SLACK_CONVERSATIONS_HISTORY_ENDPOINT "/api/conversations.history"
#define SLACK_USERS_CONVERSATIONS_ENDPOINT "/api/users.conversations"

struct SlackProfile
{
  char *displayName;
  char *statusText;
  char *statusEmoji;
  int statusExpiration;
  bool error;
};

#define NUM_USERS_TO_SUPPORT 100

struct SlackUsers
{
    char *id[NUM_USERS_TO_SUPPORT];
    char *name[NUM_USERS_TO_SUPPORT];
};

struct SlackMessage
{
  char *text;
  char *username;
  char *userid;
  char *type;
  bool error;
  //char *ts;
  //char *bot_id;
};

struct SlackUsersConversations {
  JsonObject channelsObj;
  //String channelNames[22];
  //String channelIds[22];
  int  n_channels;
  char *channelNames[22];
  char *channelIds[22];
  bool is_channel;
  char *purpose[200];
  char *topic[200];
  bool error;
};


struct SlackMessages {
    int n_messages;
    struct SlackMessage messages[30];
    bool error;
};

class ArduinoSlack
{
public:
  ArduinoSlack(Client &client, const char *bearerToken);

  int makeGetRequest(const char *command);
  int makePostRequest(const char *command, const char *body, const char *contentType = "application/json");
  SlackProfile setCustomStatus(const char *text, const char *emoji, int expiration = 0);
  SlackMessage postMessage(const char *channel, const char *text);
  SlackUsersConversations usersConversations();
  SlackMessages channelHistory(char *channelId);
  bool setPresence(const char *presence);
  int portNumber = 443;
  int profileBufferSize = 10000;
  Client *client;

private:
  const char *_bearerToken;
  int getHttpStatusCode();
  void skipHeaders(bool tossUnexpectedForJSON = true);
  void closeClient();
  void stripBadDataFromClientResponse(char *payload);

  const char *getConvHistEndpointArgs =
      R"(/api/conversations.history?channel=%s&limit=%i)";
  const char *setConvoHistoryBody =
      R"({"channel": "%s", "limit": "%s"})";
  const char *setMessageBody =
      R"({"channel": "%s", "text": "%s"})";
  const char *setEndpointBody =
      R"({"profile": { "status_text": "%s","status_emoji": "%s","status_expiration": %d}})";
};

#endif
