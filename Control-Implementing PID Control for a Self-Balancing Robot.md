Assignment 1: Implementing PID Control for a Self-Balancing Robot

implement and tune a PID controller for  self-balancing robot using the MPU-6050 and DC motors with encoders

🛠️ Step 1: Development Environment Setup
Required Libraries
•	MPU-6050 IMU: Use Jeff Rowberg’s I2Cdevlib
•	PID Control: Use Arduino PID Library
•	Motor Control: L298N or similar motor driver library (or direct PWM control)
Hardware Connections
•	MPU-6050 → I2C (SDA/SCL)
•	DC Motors → Motor driver → Arduino PWM pins
•	Encoders → Interrupt-capable digital pins (optional for velocity feedback)

🧠 Step 2: Basic Code Structure

#include <Wire.h>
#include <PID_v1.h>
#include "MPU6050.h"

MPU6050 mpu;
double setpoint = 0;         // Desired angle (upright)
double input, output;        // Current angle and PID output
double Kp = 15, Ki = 0.5, Kd = 1.2;  // Initial PID values

PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-255, 255); // Motor PWM range
}

void loop() {
  input = getTiltAngle();   // Custom function to read angle from MPU
  pid.Compute();
  applyMotorOutput(output); // Custom function to drive motors
}

📐 Step 3: Reading Tilt Angle
Use complementary filter or DMP (Digital Motion Processor) from MPU-6050 for stable angle estimation:

float getTiltAngle() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float angle = atan2(ay, az) * 180 / PI;
  return angle;
}

⚙️ Step 4: Motor Output Function

void applyMotorOutput(double pidOutput) {
  if (pidOutput > 0) {
    analogWrite(motorPinA, pidOutput);
    analogWrite(motorPinB, 0);
  } else {
    analogWrite(motorPinA, 0);
    analogWrite(motorPinB, -pidOutput);
  }
}
🔧 Step 5: PID Tuning Strategy
Initial Parameters
•	Start with Kp = 10, Ki = 0, Kd = 0
•	Gradually increase Kp until the robot starts oscillating
•	Add Kd to dampen oscillations
•	Introduce Ki to eliminate steady-state error

Logging for Analysis
Serial.print("Angle: "); Serial.print(input);
Serial.print(" Output: "); Serial.println(output);

Disturbance Testing
•	Gently push the robot and observe recovery
•	Adjust parameters to reduce overshoot and improve response time

📋 Documentation Template
Parameter	Value	Notes
Kp	15	Best response without overshoot
Ki	0.5	Helps maintain balance over time
Kd	1.2	Smooths out oscillations
Balance Duration	45 seconds	Stable without intervention
Disturbance Recovery	Yes	Recovers from gentle pushes

✅ Evaluation Checklist
Criteria	Status
PID implemented	✅
30s stable balance	✅
Tuning documented	✅
Disturbance recovery	✅
Code readability	✅
