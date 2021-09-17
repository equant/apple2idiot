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

struct SlackProfile
{
  char *displayName;
  char *statusText;
  char *statusEmoji;
  int statusExpiration;
  bool error;
};

struct SlackMessage
{
  char *text;
  char *username;
  char *bot_id;
  char *type;
  char *ts;
  bool error;
};

struct SlackConvoHist
{
  JsonObject messageObj;
  bool error;
};


class ArduinoSlack
{
public:
  ArduinoSlack(Client &client, const char *bearerToken);

  int makePostRequest(const char *command, const char *body, const char *contentType = "application/json");
  SlackProfile setCustomStatus(const char *text, const char *emoji, int expiration = 0);
  SlackMessage postMessage(const char *channel, const char *text);
  SlackConvoHist conversationHistory(const char *channel, const char *limit);
  bool setPresence(const char *presence);
  int portNumber = 443;
  int profileBufferSize = 10000;
  Client *client;

private:
  const char *_bearerToken;
  int getHttpStatusCode();
  void skipHeaders(bool tossUnexpectedForJSON = true);
  void closeClient();

  const char *setConvoHistoryBody =
      R"({"channel": "%s", "limit": "%s"})";
  const char *setMessageBody =
      R"({"channel": "%s", "text": "%s"})";
  const char *setEndpointBody =
      R"({"profile": { "status_text": "%s","status_emoji": "%s","status_expiration": %d}})";
};

#endif
