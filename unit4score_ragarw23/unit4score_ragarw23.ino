 // CS 362
 // Group Project - Whack a Mole
 // Rishika Agarwal
 // subsystem 4
 // Scoreboard to keep track of whacker's score
 
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int startBtn = 2;
volatile int score_receiver = 0;
volatile int incoming_sig;

volatile int score_reset;
volatile int counter = 0;
const int rxPin = 8;
const int txPin = 9;
SoftwareSerial myserial(rxPin, txPin);
 
//setup function
void setup() {
  pinMode(startBtn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startBtn),startBtnPress, RISING);
  lcd.begin(16, 2);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(9600);
  myserial.begin(9600);
  Serial.println("<Arduino is ready>");

  //initial display on first line
  lcd.setCursor(0,0);
  String line1 = "Score";
  lcd.print(line1);
  
}// end of function

void loop() {
  //display of actual score on the second line
  lcd.setCursor(0,1);
  // keep tracks of whacker's score
  lcd.print(counter);

  // to read if the signal is incoming
  if(myserial.available() > 0) {
    incoming_sig = myserial.read();
    Serial.println(incoming_sig, DEC);
  }

  // if signal is 1 or high, then increase the score by one
  if(incoming_sig == 1){ 

    incoming_sig = 0;
    lcd.setCursor(0,1);
    counter = counter + 1;
    lcd.print(counter);
    lcd.print("           ");
  } 

  // if the game has to be restarted
  if(score_reset == 1) {
    counter = 0;
    score_reset = 0;
  }
  
}// end of function

// score resets on pressing the push button
void startBtnPress(){
  score_reset = 1;
}
