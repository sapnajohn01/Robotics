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
