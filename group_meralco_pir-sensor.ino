#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define pirSensor 2 // initialize pir sensor pin
#define buzzer 3 // initialize buzzer pin
#define sensorValue boolean // initialize sensorvalue as boolean, maarte kasi ung program di raw narerecognize sa main

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(pirSensor, INPUT); // initialize the PIR sensor as input value for the buzzer 
  pinMode(buzzer, OUTPUT); // initialize the buzzer as output
  Serial.begin(9600); // starting up serial monitor
	lcd.begin(); // set the resolution of 16 by 2 display
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("ALL CLEAR : )");

  check_For_Intruder();
}

void check_For_Intruder() {
  boolean sensorValue = digitalRead(pirSensor); // reads the value of the pir sensor

  if (sensorValue == 1) {
    digitalWrite(buzzer, HIGH); // turn on buzzer
    //megalovania();
    //carAlarm();
    lcd.setCursor(0, 0); // column 0, row 0
    lcd.print("Intruder in the ");
    lcd.setCursor(0, 1); // column 0, row 1
    lcd.print("House : (");
    
    delay(3000);

    lcd.clear();
  }

  else {
    digitalWrite(buzzer, LOW); // turn off buzzer
  }

  delay(10);
}

void megalovania() {
tone(3,294,125);//D4
delay(125);
tone(3,294,125);//D4
delay(125);
tone(3,587,250);//D5
delay(250);
tone(3,440,250);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,587,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,247,125);//B3
delay(125);
tone(3,247,125);//B3
delay(125);
tone(3,587,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,233,62);//Bb3
delay(62);
tone(3,233,62);//Bb3
delay(62);
tone(3,233,62);//Bb3
delay(62);
tone(3,233,62);//Bb3
delay(62);
tone(3,587,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,294,125);//D4
delay(125);
tone(3,294,125);//D4
delay(125);
tone(3,587,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,261,125);//C4(middle)     
delay(62);
tone(3,587,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,247,125);//B3
delay(125);
tone(3,247,125);//B3
delay(125);
tone(3,587,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);
tone(3,233,62);//Bb3
delay(62);
tone(3,233,62);//Bb3
delay(62);
tone(3,233,62);//Bb3
delay(62);
tone(3,233,62);//Bb3
delay(62);
tone(3,588,250);//D5
delay(250);
tone(3,440,375);//A4
delay(375);
tone(3,415,125);//Ab4
delay(250);
tone(3,392,250);//G4
delay(250);
tone(3,349,250);//F4
delay(250);
tone(3,294,125);//D4
delay(125);
tone(3,349,125);//F4
delay(125);
tone(3,392,125);//G4
delay(125);

/*
//DOEH DEH DEH AH DAH DOOEH DOO AH (INTENSIFIES)

tone(3,587,125);//D5
delay(125);
tone(3,587,125);//D5
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,523,125);//C5
delay(125);
tone(3,523,125);//C5
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,494,125);//B4
delay(125);
tone(3,494,125);//B4
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,466,125);//Bb4
delay(125);
tone(3,466,125);//Bb4
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,587,125);//D5
delay(125);
tone(3,587,125);//D5
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,523,125);//C5
delay(125);
tone(3,523,125);//C5
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,494,125);//B4
delay(125);
tone(3,494,125);//B4
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
tone(3,466,125);//Bb4
delay(125);
tone(3,466,125);//Bb4
delay(125);
tone(3,1175,250);//D6
delay(250);
tone(3,880,250);//A5
delay(325);
tone(3,831,125);//Ab5
delay(250);
tone(3,784,250);//G5
delay(250);
tone(3,698,250);//F5
delay(250);
tone(3,587,125);//D5
delay(125);
tone(3,698,125);//F5
delay(125);
tone(3,784,125);//G5
delay(125);
*/
}

void carAlarm() {
tone(3, 500);
delay(100);
tone(3, 1000);
delay(100);
tone(3, 500);
delay(100);
tone(3, 1000);
delay(100);
tone(3, 500);
delay(100);
tone(3, 1000);
delay(100);
tone(3, 500);
delay(100);
tone(3, 1000);
delay(100);
tone(3, 500);
delay(100);
tone(3, 1000);
delay(100);
tone(3, 500);
delay(100);
tone(3, 1000);
delay(100);
}