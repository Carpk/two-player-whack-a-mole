



int commPin = A1;


void setup() {
  pinMode(commPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
//  analogWrite(commPin, 1);
  Serial.write(1);
  delay(10000);

//  analogWrite(commPin, 0);
  Serial.write(0);
  delay(10000);
}
