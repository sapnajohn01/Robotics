
#include <Servo.h>
#include <Stepper.h>

// DC Motor Pins
const int ENA = 5;     // PWM pin
const int IN1 = 2;
const int IN2 = 3;

// Servo Motor
Servo myServo;
const int servoPin = 9;

// Stepper Motor
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7); // IN1–IN4

void setup() {
  // DC Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Servo setup
  myServo.attach(servoPin);

  // Stepper setup
  myStepper.setSpeed(10); // RPM
}

void loop() {
  runDCMotor();
  sweepServo();
  rotateStepper();
}

void runDCMotor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  for (int speed = 0; speed <= 255; speed += 50) {
    analogWrite(ENA, speed);
    delay(500);
  }
  analogWrite(ENA, 0);
  delay(1000);
}

void sweepServo() {
  for (int angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    delay(200);
  }
  for (int angle = 180; angle >= 0; angle -= 10) {
    myServo.write(angle);
    delay(200);
  }
}

void rotateStepper() {
  myStepper.step(stepsPerRevolution); // One full rotation
  delay(1000);
}
