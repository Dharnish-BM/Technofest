#include <Servo.h>

Servo regulator;
const int gasPin = A0;
const int buzzerPin = 8;
const int fanPin = 7;
int threshold = 260;

unsigned long fanOnTime = 0;
bool fanRunning = false;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  
  regulator.attach(9);
  regulator.write(0);
}

void loop() {
  int gasValue = analogRead(gasPin);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);


  if (gasValue > threshold) {
    Serial.println("🚨 Gas Leak Detected!");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(fanPin, HIGH);
    fanOnTime = millis();
    fanRunning = true;
    regulator.write(90);
    delay(2000);
    digitalWrite(buzzerPin, LOW);
  }


  if (fanRunning && (millis() - fanOnTime >= 10000)) {
    digitalWrite(fanPin, LOW);
    fanRunning = false;
    regulator.write(0); 
  }

  delay(200);
}
