Assignment 3: Robot Power Management System
Here's a complete breakdown of the power management system for your mobile robot, combining hardware design and Arduino code to meet all your objectives.

⚡ System Overview
This system includes:
•	Battery voltage monitoring via a voltage divider
•	Low-voltage cutoff using MOSFETs
•	Independent power control for motors and sensors
•	Visual LED indicators for battery status
🔧 Hardware Design
1. Voltage Divider Circuit
To safely read 9V–12V battery levels on an Arduino analog pin (max 5V), use a voltage divider:
Target: Scale 12V down to ≤5V Formula:
 
Recommended Resistors:
•	R1 = 10kΩ
•	R2 = 4.7kΩ
•	Max input:
 
Connect:
•	Battery + to R1
•	R1 to R2
•	R2 to GND
•	Junction of R1/R2 to Arduino A0
2. MOSFET Power Control
Use N-channel MOSFETs (e.g., IRF540N) to switch power to:
•	Motors
•	Sensors
Connections:
•	Drain → Component GND
•	Source → Battery GND
•	Gate → Arduino digital pin (via 220Ω resistor)
Add flyback diodes across motor terminals for protection.
3. LED Indicators
Use 3 LEDs:
•	Green → Battery OK
•	Yellow → Warning (e.g., <8V)
•	Red → Critical (<7V)
Connect each LED with a 220Ω resistor to digital pins.
const int voltagePin = A0;
const float R1 = 10000.0; // 10kΩ
const float R2 = 4700.0;  // 4.7kΩ

const int motorMOSFET = 3;
const int sensorMOSFET = 4;

const int ledGreen = 5;
const int ledYellow = 6;
const int ledRed = 7;

void setup() {
  pinMode(motorMOSFET, OUTPUT);
  pinMode(sensorMOSFET, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  Serial.begin(9600);
}

float readBatteryVoltage() {
  int analogValue = analogRead(voltagePin);
  float vOut = analogValue * (5.0 / 1023.0);
  float vIn = vOut * ((R1 + R2) / R2);
  return vIn;
}

void loop() {
  float batteryVoltage = readBatteryVoltage();
  Serial.println(batteryVoltage);

  if (batteryVoltage > 8.0) {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(motorMOSFET, HIGH);
    digitalWrite(sensorMOSFET, HIGH);
  } else if (batteryVoltage > 7.0) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(motorMOSFET, HIGH);
    digitalWrite(sensorMOSFET, HIGH);
  } else {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(motorMOSFET, LOW); // Cutoff motors
    digitalWrite(sensorMOSFET, HIGH); // Sensors still active
  }

  delay(1000);
}

🧪 Test & Validation
•	Simulate voltage drop using a variable power supply or battery drain.
•	Confirm LED status and MOSFET switching behavior.
•	Use Serial.println() to monitor voltage readings.
