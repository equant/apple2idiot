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
#define D0R 12
#define D1R 13
#define D2R 14
#define D3R 15
#define D4R 18
#define D5R 19
#define D6R 21
#define D7R 22

byte data_pins[] = {D0R, D1R, D2R, D3R, D4R, D5R, D6R, D7R};
#define DATA_BUS_SIZE 8

#define A0R 23
#define A1R 25
#define A2R 26
#define A3R 27

byte address_pins[] = {A0R, A1R, A2R, A3R};
#define ADDRESS_BUS_SIZE 4

//#define DEVSEL_PIN      35
#define DEVSEL_PIN      5

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
    Serial.println("^INTERUPT!");
}

/*################################################
#                     Setup                      #
################################################*/

void setup() {
    //for (int i=0; i < 8; i++) {
        //pinMode(DATA_0_PIN + i, INPUT);
    //}
    pinMode(A0R, OUTPUT); digitalWrite(A0R, LOW);
    pinMode(A1R, OUTPUT); digitalWrite(A1R, LOW);
    pinMode(A2R, OUTPUT); digitalWrite(A2R, LOW);
    pinMode(A3R, OUTPUT); digitalWrite(A3R, LOW);
    pinMode(D0R, INPUT);
    pinMode(D1R, INPUT);
    pinMode(D2R, INPUT);
    pinMode(D3R, INPUT);
    pinMode(D4R, INPUT);
    pinMode(D5R, INPUT);
    pinMode(D6R, INPUT);
    pinMode(D7R, INPUT);
    pinMode(DEVSEL_PIN, INPUT);
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Starting...");
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, LOW);
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, FALLING);
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, RISING);
    //attachInterrupt(DEVSEL_PIN, isrDEVSEL, FALLING);
}

void set_address(int address) {

    Serial.print("Setting address (");
    Serial.print(address);
    Serial.print("): ");
    for (byte i=0; i<ADDRESS_BUS_SIZE; i++) {
        byte state = bitRead(address, i);
        digitalWrite(address_pins[i], state);
        Serial.print(state);
    }
    Serial.println();
}

unsigned long read_data() {
    unsigned long data_bus_read = 0;
    Serial.print("Reading data: ");
    for (byte i=0; i<DATA_BUS_SIZE; i++) {
        data_bus_read << 1;
        byte pin_state = digitalRead(data_pins[i]);
        Serial.print(pin_state);
        data_bus_read += pin_state;
    }
    Serial.print(data_bus_read);
    Serial.println();

    delay(10);
    raw_register_read = REG_READ(GPIO_IN_REG);
    //raw_register1_read = REG_READ(GPIO_IN1_REG);
    Serial.print(raw_register_read, BIN);
    //Serial.print(" : ");
    //Serial.println(raw_register1_read, BIN);
    Serial.println();
    return data_bus_read; 
}


/*################################################
#                      Main                      #
################################################*/

const long loopTimeInterval = 5500;           // interval at which to blink (milliseconds)
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

    //if (millis() - lastLoopMillis > loopTimeInterval) {
        //Serial.print("RAWDATA: ");
        //Serial.println(raw_register_read, BIN);
        //raw_register_read = REG_READ(GPIO_IN_REG);
        //Serial.println("--LOOP CALLED ISR--");
        //isrDEVSEL();
        //raw_register_read = REG_READ(GPIO_IN_REG);
        //raw_register1_read = REG_READ(GPIO_IN1_REG);
        //isr_handled = true;
        //lastLoopMillis = millis();
    //}
    delay(5555);
    for (int i=0; i < ADDRESS_BUS_SIZE; i++) {
        set_address(i);
        long foo = read_data();
        delay(100);
    }
    
}
