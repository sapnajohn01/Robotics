Assignment 2: Multi-Sensor Data Acquisition System

Here's a complete step-by-step guide and Arduino sketch to build your environmental monitoring prototype using:
•	Ultrasonic sensor (HC-SR04) – digital
•	Analog temperature sensor (LM35) – analog
•	IR obstacle sensor – digital
🛠️ Hardware Setup
🔌 Wiring Overview
Sensor	Arduino Pin	Notes
HC-SR04 (Trig/Echo)	D9 / D10	Use 5V logic, no pull-up needed
LM35 (Analog Temp)	A0	Use voltage divider if Vout > 5V
IR Obstacle Sensor	D2	Use pull-up resistor if noisy signal
🧮 Signal Filtering & Calibration
•	Moving Average Filter: Smooths out fluctuations over 5 samples.
•	Calibration:
o	LM35: Offset based on ambient temperature reference.
o	HC-SR04: Adjust for known distance.
o	IR Sensor: Binary (0/1), no calibration needed.

// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int tempPin = A0;
const int irPin = 2;

// Moving average buffers
const int bufferSize = 5;
float tempBuffer[bufferSize], distBuffer[bufferSize];
int tempIndex = 0, distIndex = 0;

// Calibration offsets
float tempOffset = 0.0;
float distOffset = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT);
}

float readUltrasonic() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // cm
  return distance;
}

float readTemperature() {
  int raw = analogRead(tempPin);
  float voltage = raw * (5.0 / 1023.0);
  float tempC = voltage * 100; // LM35: 10mV/°C
  return tempC;
}

float movingAverage(float buffer[], float newVal, int &index) {
  buffer[index] = newVal;
  index = (index + 1) % bufferSize;
  float sum = 0;
  for (int i = 0; i < bufferSize; i++) sum += buffer[i];
  return sum / bufferSize;
}

void loop() {
  float rawTemp = readTemperature();
  float rawDist = readUltrasonic();
  int irValue = digitalRead(irPin);

  float filtTemp = movingAverage(tempBuffer, rawTemp, tempIndex);
  float filtDist = movingAverage(distBuffer, rawDist, distIndex);

  float calTemp = filtTemp + tempOffset;
  float calDist = filtDist + distOffset;

  // Display formatted table
  Serial.println("--------------------------------------------------");
  Serial.println("| Sensor        | Raw Value | Calibrated Value   |");
  Serial.println("--------------------------------------------------");
  Serial.print("| Temperature   | ");
  Serial.print(rawTemp, 1); Serial.print(" °C   | ");
  Serial.print(calTemp, 1); Serial.println(" °C         |");

  Serial.print("| Distance      | ");
  Serial.print(rawDist, 1); Serial.print(" cm   | ");
  Serial.print(calDist, 1); Serial.println(" cm         |");

  Serial.print("| IR Obstacle   | ");
  Serial.print(irValue); Serial.print("        | ");
  Serial.print(irValue == 1 ? "No Obstacle     " : "Obstacle Detected");
  Serial.println(" |");
  Serial.println("--------------------------------------------------\n");
  delay(1000);
}
🧪 Calibration Tips
•	Temperature: Compare with a digital thermometer and adjust tempOffset.
•	Distance: Use a ruler to measure known distances and adjust distOffset.
•	IR Sensor: Test with hand/object at various distances to confirm detection threshold.
--------------------------------------------------
| Sensor        | Raw Value | Calibrated Value   |
--------------------------------------------------
| Temperature   | 28.3 °C   | 28.8 °C            |
| Distance      | 52.7 cm   | 53.2 cm            |
| IR Obstacle   | 0         | Obstacle Detected  |
--------------------------------------------------
