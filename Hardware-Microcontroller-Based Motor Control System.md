
Assignment 1: Microcontroller-Based Motor Control System

This is a perfect hands-on demo to showcase motor control fundamentals. Here's a complete breakdown to help you build a modular, classroom-ready system:
🧠 System Overview
You'll be using:
•	Arduino Uno as the microcontroller
•	L298N for DC motor control
•	ULN2003 for stepper motor (28BYJ-48)
•	Servo motor (e.g., SG90) directly on PWM pin
•	External power supply (e.g., 7.5V adapter or battery pack) for motor drivers
🔌 Wiring Summary
Motor Type	Driver	Arduino Pins	Power Source	Notes
DC Motor	L298N	ENA (PWM), IN1, IN2	External 7.5–12V	ENA for speed control
Servo	None	PWM pin (e.g., D9)	5V regulated	Use capacitor across VCC-GND
Stepper	ULN2003	IN1–IN4 (e.g., D4–D7)	External 5V	28BYJ-48 motor

🧾 Arduino Code (Modular & Commented)
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
🔋 Hardware Components Tips
•	DC Motor: Use external 7.5–12V supply to L298N's VCC. Connect GND to Arduino GND.
•	Servo: Use a capacitor (e.g., 470µF) across 5V and GND to smooth current spikes.
•	Stepper: Power ULN2003 from external 5V. Avoid powering motors directly from Arduino 5V pin.

🧰 Presentation & Modularity
•	Use color-coded jumper wires and breadboard labels for clarity.
•	Mount components on a laser-cut acrylic base or 3D-printed chassis.
•	Modularize code into separate .ino files or functions for each motor type.
•	Add toggle switches or buttons to activate motors individually for demo control.
