Assignment 2: Modular Search and Rescue Robot

📁 1. motorControl.ino\
// Motor Control Module\
const int motorLeftFwd = 3;\
const int motorLeftRev = 4;\
const int motorRightFwd = 5;\
const int motorRightRev = 6;\
const int speedPinLeft = 9;\
const int speedPinRight = 10;

void setupMotors() {\
  pinMode(motorLeftFwd, OUTPUT);\
  pinMode(motorLeftRev, OUTPUT);\
  pinMode(motorRightFwd, OUTPUT);\
  pinMode(motorRightRev, OUTPUT);\
  pinMode(speedPinLeft, OUTPUT);\
  pinMode(speedPinRight, OUTPUT);
}

void moveForward(int speed) {\
  analogWrite(speedPinLeft, speed);\
  analogWrite(speedPinRight, speed);\
  digitalWrite(motorLeftFwd, HIGH);\
  digitalWrite(motorLeftRev, LOW);\
  digitalWrite(motorRightFwd, HIGH);\
  digitalWrite(motorRightRev, LOW);
}

void turnRight(int speed) {\
  analogWrite(speedPinLeft, speed);\
  analogWrite(speedPinRight, speed);\
  digitalWrite(motorLeftFwd, HIGH);\
  digitalWrite(motorLeftRev, LOW);\
  digitalWrite(motorRightFwd, LOW);\
  digitalWrite(motorRightRev, HIGH);
}

void stopMotors() {\
  digitalWrite(motorLeftFwd, LOW);\
  digitalWrite(motorLeftRev, LOW);\
  digitalWrite(motorRightFwd, LOW);\
  digitalWrite(motorRightRev, LOW);
}

📁 2. ultrasonicSensor.ino\
// Ultrasonic Sensor Module\
const int trigPin = A0;\
const int echoPin = A1;

void setupUltrasonic() {\
  pinMode(trigPin, OUTPUT);\
  pinMode(echoPin, INPUT);
}

float getDistanceCM() {\
  digitalWrite(trigPin, LOW);\
  delayMicroseconds(2);\
  digitalWrite(trigPin, HIGH);\
  delayMicroseconds(10);\
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);\
  float distance = duration * 0.034 / 2;

  // Simple noise filtering\
  if (distance < 2 || distance > 400) return -1;\
  return distance;
}

📁 3. infraredSensor.ino\
// Infrared Sensor Module\
const int irPin = A2;

void setupIR() {\
  pinMode(irPin, INPUT);
}

bool isObjectDetected() {\
  int value = analogRead(irPin);\
  return value < 500;  // Threshold for detection
}

📁 4. mainProgram.ino\
// Main Program\
#include "motorControl.ino"\
#include "ultrasonicSensor.ino"\
#include "infraredSensor.ino"

void setup() {\
  Serial.begin(9600);\
  setupMotors();\
  setupUltrasonic();\
  setupIR();
}

void loop() {\
  float distance = getDistanceCM();\
  bool irDetected = isObjectDetected();

  Serial.print("Distance: ");\
  Serial.print(distance);\
  Serial.print(" cm | IR: ");\
  Serial.println(irDetected ? "Object Detected" : "Clear");

  if (distance > 20 && !irDetected) {\
    moveForward(150);\
    Serial.println("Moving Forward");\
  } else {\
    stopMotors();\
    delay(500);\
    turnRight(150);\
    Serial.println("Turning Right");\
    delay(1000);\
  }\
  delay(200);\
}

// Main Program\
#include "motorControl.ino"\
#include "ultrasonicSensor.ino"\
#include "infraredSensor.ino"

void setup() {\
  Serial.begin(9600);\
  setupMotors();\
  setupUltrasonic();\
  setupIR();\
}

void loop() {\
  float distance = getDistanceCM();\
  bool irDetected = isObjectDetected();

  Serial.print("Distance: ");\
  Serial.print(distance);\
  Serial.print(" cm | IR: ");\
  Serial.println(irDetected ? "Object Detected" : "Clear");

  if (distance > 20 && !irDetected) {\
    moveForward(150);\
    Serial.println("Moving Forward");\
  } else {\
    stopMotors();\
    delay(500);\
    turnRight(150);\
    Serial.println("Turning Right");\
    delay(1000);\
  }\
  delay(200);\
}

✅ Evaluation Highlights\
Criteria	Implementation Notes\
Modular Design	Each function in its own tab/module\
Reusability	Parameterized motor/sensor functions\
Serial Debugging	Sensor values, motor states, transitions\
Consistent Behavior	Obstacle avoidance loop with fallback\
Documentation	Clear comments and modular structure

