//wifi module
#include <SoftwareSerial.h>
#define baudRate 115200
#define DEBUG true

// RX | TX
SoftwareSerial ESPserial(7, 8);

//leds
#define led_1 11
#define led_2 10
#define led_3 9

//potentiometer
#define potenPin A0

int ledItems = 3;

//setting up leds as output
void setup() {
  //communication with the host computer 
  Serial.begin(baudRate);

  //start the software serial for communication with the esp8266
  ESPserial.begin(baudRate);

  Serial.println("");
  Serial.println("Remember to set Both NL & CR in the serial monitor.");
  Serial.println("Ready");
  Serial.println("");
  
  //MAIN SETUP
  //output for leds
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
}

void loop() {
  // listen for communication from the ESP8266 and then write it to the serial monitor
  if (ESPserial.available()) {
    Serial.write(ESPserial.read());
  }

  // listen for user input and send it to the ESP8266
  if (Serial.available()) {
    ESPserial.write(Serial.read());
  }

  int potenValue = analogRead(potenPin);

  if (potenValue <= 1024 / 3) {
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
  } else if (potenValue <= 1024 / 2 && potenValue > 1024 / 3) {
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, HIGH);
    digitalWrite(led_3, LOW);
  } else {
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, HIGH);
  }
}

