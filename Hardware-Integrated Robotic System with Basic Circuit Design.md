Assignment 5: Integrated Robotic System with Basic Circuit Design

This is a perfect showcase opportunity for a robotics education company—and right up your alley. Here's a complete breakdown of the mobile robot platform design, from circuit architecture to autonomous behaviour.
🧠 System Overview
Core Components:
•	Arduino Uno (or Nano for compact builds)
•	L298N Motor Driver Module
•	2x DC Motors (with wheels)
•	HC-SR04 Ultrasonic Sensor (front obstacle detection)
•	2x IR Sensors (left and right side detection)
•	Power Supply: 7.4V Li-ion battery for motors, 5V regulated supply for Arduino
•	Perfboard or prototype board for permanent circuit
🔌 Circuit Design & Wiring
✅ Power Management
•	Motors: Powered by 7.4V Li-ion battery via L298N
•	Arduino & Sensors: Powered by 5V regulated supply (can be derived using buck converter from 7.4V battery)
•	⚙️ Connections Summary
Component	Arduino Pins	Notes
L298N IN1, IN2	D2, D3	Motor A control
L298N IN3, IN4	D4, D5	Motor B control
L298N ENA, ENB	Connected to 5V	Enable motors
HC-SR04	Trig: D6, Echo: D7	Distance sensing
IR Sensor Left	A0	Analog input
IR Sensor Right	A1	Analog input
Power Supply	VIN, GND	Regulated 5V to Arduino

🧾 Circuit Diagram
I've included a few reference diagrams below to guide your implementation. These show how to wire the motor driver, sensors, and Arduino together for full integration.

🔧 Implementation Tips
•	Use male headers and solder bridges on perfboard for clean layout.
•	Keep motor power lines separate from logic power to avoid noise.
•	Add decoupling capacitors near sensors and motor driver for stability.
•	Label all connections clearly for educational clarity.

🤖 Autonomous Behavior Logic
Behavior Flow:
1.	Move Forward until obstacle detected by ultrasonic sensor.
2.	Check IR Sensors:
o	If left is clear → turn left.
o	If right is clear → turn right.
o	If both blocked → back up, then recheck.
3.	Resume Forward Motion when clear.
Sample Arduino Logic (Pseudocode):

if (ultrasonicDistance > threshold) {
  moveForward();
} else {
  if (IR_left_clear && !IR_right_clear) {
    turnLeft();
  } else if (!IR_left_clear && IR_right_clear) {
    turnRight();
  } else {
    backUp();
    delay(1000);
  }
}

🖼️ Reference Circuit Diagrams
Here are some visual guides to help you wire everything correctly:
•	Obstacle Avoidance Robot Circuit Guide
•	GitHub Repository with Circuit Diagrams and Code

