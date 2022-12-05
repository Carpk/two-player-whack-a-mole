// Name: Jonah Covarrubias 661743147
// UNIT 1 CODE
// Description - This code starts the game and controls the countdown for game time.
// Assumptions - start button to: pin 2
//               serial rx and tx to: Mole Arduino
//               lcd rs to:12, lcd en to:11, lcd d4 to:6, lcd d5 to:5, lcd d6 to:4, lcd d7 to:3
// References - None



#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int startBtn = 2;
const int debugPin = 7;
volatile bool gameStarted = false;
volatile unsigned long originalTime = 0;
volatile int countdown = 30;

void setup() {
  // put your setup code here, to run once:
  pinMode(startBtn, INPUT_PULLUP);
  pinMode(debugPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(startBtn),startBtnPress, RISING);

  Serial.begin(9600);
  lcd.begin(16, 2);
  digitalWrite(debugPin, LOW);
  // Serial.write(0); //game might start early because of unknown reads before tx pin plugged in
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  unsigned int displayTime = countdown - ((millis() - originalTime) / 1000);
  char buffer[25];
  if(gameStarted)
  {
    if(displayTime + 1 > 0)
    {
      sprintf(buffer, "%d seconds          ", displayTime);
      lcd.print(buffer);
    } else {
      lcd.print("Game Over            ");
      gameStarted = false;
      digitalWrite(debugPin,LOW);
      Serial.write(0);
    }
  }
}

void startBtnPress(){
  if(!gameStarted){
    gameStarted = true;
    originalTime = millis();
    digitalWrite(debugPin, HIGH);
    Serial.write(1);
  }
}