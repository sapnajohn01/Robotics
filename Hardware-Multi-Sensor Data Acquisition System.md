**Assignment 2: Multi-Sensor Data Acquisition System**

🧠 **System Overview**\
•	Ultrasonic sensor (HC-SR04) – digital\
•	Analog temperature sensor (LM35) – analog\
•	IR obstacle sensor – digital

🛠️ **Hardware Setup**\
🔌 **Wiring Overview**\
Sensor	Arduino Pin	Notes\
HC-SR04 (Trig/Echo)	D9 / D10	Use 5V logic, no pull-up needed\
LM35 (Analog Temp)	A0	Use voltage divider if Vout > 5V\
IR Obstacle Sensor	D2	Use pull-up resistor if noisy signal

🧮 **Signal Filtering & Calibration**\
•	Moving Average Filter: Smooths out fluctuations over 5 samples.\
•	Calibration:\
o	LM35: Offset based on ambient temperature reference.\
o	HC-SR04: Adjust for known distance.\
o	IR Sensor: Binary (0/1), no calibration needed.

[**Sensor.ino**](https://github.com/sapnajohn01/Robotics/blob/main/Sensor.ino)

🧪 **Calibration Tips**\
•	Temperature: Compare with a digital thermometer and adjust tempOffset.\
•	Distance: Use a ruler to measure known distances and adjust distOffset.\
•	IR Sensor: Test with hand/object at various distances to confirm detection threshold.

--------------------------------------------------
| Sensor        | Raw Value | Calibrated Value   |
--------------------------------------------------
| Temperature   | 28.3 °C   | 28.8 °C            |
| Distance      | 52.7 cm   | 53.2 cm            |
| IR Obstacle   | 0         | Obstacle Detected  |
--------------------------------------------------
