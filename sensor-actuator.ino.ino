#include <Servo.h>
Servo myServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;
const int lightPin = A0;
const int motorPin = 5;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

long readDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void loop() {
  long distance = readDistance();
  int angle = map(distance, 2, 100, 0, 180);
  myServo.write(angle);

  int lightLevel = analogRead(lightPin);
  int motorSpeed = map(lightLevel, 0, 1023, 0, 255);
  analogWrite(motorPin, motorSpeed);

  Serial.print("Distance: "); Serial.print(distance);
  Serial.print(" cm | Light: "); Serial.print(lightLevel);
  Serial.print(" | Motor Speed: "); Serial.println(motorSpeed);

  delay(100);
}
