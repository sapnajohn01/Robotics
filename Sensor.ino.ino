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
