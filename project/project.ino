// 1- Shawn Klein - 670231431
// 2- Project - 
// 3- Description - game
// 4- Assumptions - I'm tired
// 5- References - other labs for resistor size
// 6- Demo: 


#include <TimeLib.h>
#include <SoftwareSerial.h>

const int but1 = 2;
const int but2 = 3;
const int but3 = 4;

const int led1 = 10;
const int led2 = 11;
const int led3 = 12;

int butPins[] = {but1, but2, but3};
int ledPins[] = {led1, led2, led3};
int randNum;
int incomingByte;

const int rxPin = 7;
const int txPin = 6;
SoftwareSerial sSerial(rxPin, txPin);

int active = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  sSerial.begin(9600);
  SoftwareSerial(rxPin, txPin);
  Serial.println("<Arduino is ready>");
}



void loop() {
  if (sSerial.available() > 0) {
    active = sSerial.read();
    Serial.println(active, DEC);
  }


  while (active) {
    randNum = random(3);
    bool penalty = false;

    unsigned long currTime = millis() + 600;
    digitalWrite(ledPins[randNum], HIGH);
    while(millis() < currTime) {
      if (digitalRead(butPins[randNum])) {
        penalty = true;
      }
    }
    digitalWrite(ledPins[randNum], LOW);

    if (penalty) {  
      currTime = millis() + 500;
    } else {  
      currTime = millis() + 700;
    }

    Serial.write(1);
    while (millis() < currTime) {
//      Serial.write(1); // digitalWrite(outGamePin, HIGH);
    }
    Serial.write(0); // digitalWrite(outGamePin, LOW);
    
    if (sSerial.available() > 0) {
      active = sSerial.read();
    }
    
    Serial.println(active, DEC);
  }
}

//  if (Serial.available() > 0) {
//        incomingByte = Serial.read();
//        Serial.println(incomingByte, DEC);
//  }


//Serial.print(analogRead(A0));
//  Serial.print(" ");
//  Serial.println(analogRead(A1));
//  // wait a bit for the analog-to-digital converter to stabilize after the last
//  // reading:
//  delay(2);

  
