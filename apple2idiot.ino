/*
*/

// Load Wi-Fi library
//#include <WiFi.h>

// Replace with your network credentials
//const char* ssid = "GSO";
//const char* password = "xerxes27";
//WiFiServer server(80);
//String http_header;

/* OUTPUTS (numbers mean GPIO port) */
#define DATA_0_PIN      18
#define DATA_1_PIN      19
#define DATA_2_PIN      23
#define DATA_3_PIN      25
#define DATA_4_PIN      26
#define DATA_5_PIN      27
#define DATA_6_PIN      32
#define DATA_7_PIN      33

#define DEVSEL_PIN      35

#define ONBOARD_LED  2

uint32_t isr_time = 0;
bool isr_handled = false;

unsigned char data_register = 0;
unsigned char d0 = 0;
unsigned char d1 = 0;
unsigned char d2 = 0;
unsigned char d3 = 0;
unsigned char d4 = 0;
unsigned char d5 = 0;
unsigned char d6 = 0;
unsigned char d7 = 0;

/*################################################
#                      ISR                       #
################################################*/

void IRAM_ATTR isrDEVSEL(void) {
    isr_time = micros();
    data_register = 0;
    d0 = digitalRead(DATA_0_PIN);
    d1 = digitalRead(DATA_1_PIN);
    d2 = digitalRead(DATA_2_PIN);
    d3 = digitalRead(DATA_3_PIN);
    d4 = digitalRead(DATA_4_PIN);
    d5 = digitalRead(DATA_5_PIN);
    d6 = digitalRead(DATA_6_PIN);
    d7 = digitalRead(DATA_7_PIN);
/*
    data_register |= digitalRead(DATA_7_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_6_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_5_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_4_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_3_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_2_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_1_PIN);
    data_register = data_register << 1;
    data_register |= digitalRead(DATA_0_PIN);
*/
    isr_handled = true;
    isr_time = micros() - isr_time;
}

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);
    pinMode(DATA_0_PIN, INPUT_PULLUP);
    pinMode(DATA_1_PIN, INPUT_PULLUP);
    pinMode(DATA_2_PIN, INPUT_PULLUP);
    pinMode(DATA_3_PIN, INPUT_PULLUP);
    pinMode(DATA_4_PIN, INPUT_PULLUP);
    pinMode(DATA_5_PIN, INPUT_PULLUP);
    pinMode(DATA_6_PIN, INPUT_PULLUP);
    pinMode(DATA_7_PIN, INPUT_PULLUP);
    pinMode(DEVSEL_PIN, INPUT_PULLUP);


    /*
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    */
    Serial.println("");
    Serial.println("");
    Serial.println("Starting.");
    attachInterrupt(DEVSEL_PIN, isrDEVSEL, CHANGE);
}

/*################################################
#                      Main                      #
################################################*/

const long loopTimeInterval = 500;           // interval at which to blink (milliseconds)
int devsel_state = 0;
unsigned long lastLoopMillis = 0;

void loop() {

    if (isr_handled) {
        data_register |= d7;
        data_register = data_register << 1;
        data_register |= d6;
        data_register = data_register << 1;
        data_register |= d5;
        data_register = data_register << 1;
        data_register |= d4;
        data_register = data_register << 1;
        data_register |= d3;
        data_register = data_register << 1;
        data_register |= d2;
        data_register = data_register << 1;
        data_register |= d1;
        data_register = data_register << 1;
        data_register |= d0;
        Serial.print("ISR Took: ");
        Serial.print(isr_time );
        Serial.println("us");
        Serial.print("DATA: ");
        Serial.println(data_register);
        Serial.print("D0:");
        Serial.println(d0);
        Serial.print("D1:");
        Serial.println(d1);
        Serial.print("D2:");
        Serial.println(d2);
        Serial.print("D3:");
        Serial.println(d3);
        Serial.print("D4:");
        Serial.println(d4);
        Serial.print("D5:");
        Serial.println(d5);
        Serial.print("D6:");
        Serial.println(d6);
        Serial.print("D7:");
        Serial.println(d7);
        Serial.print(" ");
        Serial.println(data_register, BIN);
        isr_handled = false;
        Serial.print("IN_REG_READ:");
        Serial.println(REG_READ(GPIO_IN_REG));
        Serial.print("IN1_REG_READ:");
        Serial.println(REG_READ(GPIO_IN1_REG));
    }
    
    if (millis() - lastLoopMillis > loopTimeInterval) {
    
        if (digitalRead(DEVSEL_PIN) == LOW) {
            devsel_state = digitalRead(DEVSEL_PIN);
            Serial.print("DEVSEL_PIN is low and has a value of:");
            Serial.print(devsel_state);
            Serial.print(" ");
            Serial.print(devsel_state, BIN);
            Serial.println(devsel_state);
        }
        lastLoopMillis = millis();
    }
}
