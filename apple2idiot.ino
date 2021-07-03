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
#define DATA_0_PIN      12

#define DEVSEL_PIN      35

unsigned int data_byte = 0;

/* Variables shared between ISR and main code need to be volatile */
volatile bool isr_handled = false;
volatile uint32_t raw_register_read;
volatile uint16_t raw_register1_read;

/*################################################
#                      ISR                       #
################################################*/

void IRAM_ATTR isrDEVSEL(void) {
    raw_register_read = REG_READ(GPIO_IN_REG);
    raw_register1_read = REG_READ(GPIO_IN1_REG);
    isr_handled = true;
}

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    Serial.begin(115200);

    for (int i=0; i < 8; i++) {
        pinMode(DATA_0_PIN + i, INPUT);
    }
    pinMode(DEVSEL_PIN, INPUT);
    pinMode(19, INPUT);
    pinMode(21, INPUT);
    pinMode(22, INPUT);
    pinMode(23, INPUT);
    pinMode(24, INPUT);
    pinMode(25, INPUT);
    pinMode(26, INPUT);
    pinMode(27, INPUT);
    pinMode(32, INPUT);
    pinMode(33, INPUT);
    pinMode(36, INPUT);
    pinMode(39, INPUT);
    Serial.println("");
    Serial.println("Starting.");
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, LOW);
    attachInterrupt(DEVSEL_PIN, isrDEVSEL, CHANGE);
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, RISING);
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, FALLING);
}

/*################################################
#                      Main                      #
################################################*/

const long loopTimeInterval = 2500;           // interval at which to blink (milliseconds)
int devsel_state = 0;
unsigned long lastLoopMillis = 0;

void loop() {

    if (isr_handled) {
        //data_byte = raw_register_read >> 12 & 0b00000000000011111111;

        //Serial.print("RAWDATA: ");
        //Serial.println(raw_register_read, BIN);
        //Serial.print("DATA: ");
        //Serial.println(data_byte, BIN);
        //Serial.println(data_byte);
        isr_handled = false;
        Serial.print(raw_register_read, BIN);
        Serial.print(" : ");
        Serial.println(raw_register1_read, BIN);
    }

    if (millis() - lastLoopMillis > loopTimeInterval) {
        Serial.println("--LOOP READ--");
        //Serial.print("RAWDATA: ");
        //Serial.println(raw_register_read, BIN);
        //raw_register_read = REG_READ(GPIO_IN_REG);
        //Serial.println("--LOOP CALLED ISR--");
        //isrDEVSEL();
        raw_register_read = REG_READ(GPIO_IN_REG);
        raw_register1_read = REG_READ(GPIO_IN1_REG);
        isr_handled = true;
        lastLoopMillis = millis();
    }
    
}
