
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

[Motor](https://github.com/sapnajohn01/Robotics/blob/main/Motors.ino)

🔋 Hardware Components Tips
•	DC Motor: Use external 7.5–12V supply to L298N's VCC. Connect GND to Arduino GND.
•	Servo: Use a capacitor (e.g., 470µF) across 5V and GND to smooth current spikes.
•	Stepper: Power ULN2003 from external 5V. Avoid powering motors directly from Arduino 5V pin.

🧰 Presentation & Modularity
•	Use color-coded jumper wires and breadboard labels for clarity.
•	Mount components on a laser-cut acrylic base or 3D-printed chassis.
•	Modularize code into separate .ino files or functions for each motor type.
•	Add toggle switches or buttons to activate motors individually for demo control.
