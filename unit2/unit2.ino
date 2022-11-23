
#include <TimeLib.h>
#include <SoftwareSerial.h>


const int inGamePin = 7;
const int outGamePin = 6;

const int but1 = 2;
const int but2 = 3;
const int but3 = 4;

const int led1 = 10;
const int led2 = 11;
const int led3 = 12;

int butPins[] = {but1, but2, but3};
int ledPins[] = {led1, led2, led3};
int randNum;

int val = 0;
const int rxPin = 7;
const int txPin = 6;
SoftwareSerial sSerial(rxPin, txPin);

void setup() {
  pinMode(inGamePin, INPUT);

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
}

void loop() {
  if (sSerial.available() > 0) {
        val = sSerial.read();
  }

  // start round
  if (val) {
    // light a random pin
    randNum = random(3);
    digitalWrite(ledPins[randNum], HIGH);

    
    while(val) {
      if (digitalRead(butPins[randNum])) {
          // SEND HIGH SIGNAL TO SCORE
          Serial.write(1);
          delay(200); // stay below 500ms
          Serial.write(0);
      }
      
      if (sSerial.available() > 0) {
        val = sSerial.read();
      }
    }
      
    digitalWrite(ledPins[randNum], LOW);
  }
}
 
