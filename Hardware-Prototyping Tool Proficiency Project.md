**Assignment 4: Prototyping Tool Proficiency Project**

🛠️ **System Overview**\
You'll build a dual sensor-actuator setup:\
•	Sensor 1: Ultrasonic sensor → Actuator 1: Servo motor (position control)\
•	Sensor 2: Light sensor (photoresistor) → Actuator 2: DC motor (speed control)

All components will be mounted on a well-organized breadboard, powered by a regulated 5V supply, and controlled via an Arduino Uno.

🔧 **Hardware Components**\
Component	Purpose\
Arduino Uno	Microcontroller\
HC-SR04	Ultrasonic distance sensor\
Photoresistor + 10kΩ	Light sensor (voltage divider)\
Servo motor	Position actuator\
DC motor + MOSFET	Speed actuator\
Breadboard	Prototyping platform\
Jumper wires	Connections\
LEDs (optional)	Status indicators\
Multimeter	Voltage and continuity checks\
Wire strippers	Clean wire prep\
Soldering iron	Modify or reinforce joints

🧰 **Prototyping Best Practices**\
✅ Breadboard Layout\
•	Use side rails for power (red) and ground (black)\
•	Group components logically:\
o	Left: Sensors\
o	Right: Actuators\
o	Center: Arduino connections\
•  Keep wires short and tidy\
•  Use color-coded wires:\
•	Red → Power\
•	Black → Ground\
•	Yellow/Blue/White → Signals\
✅ Tool Usage\
•	Strip wires cleanly with wire strippers\
•	Use multimeter to:\
o	Check voltage at sensor outputs\
o	Confirm MOSFET gate switching\
•	Solder headers or reinforce weak joints if needed

🔌 **Circuit Connections**\
1. Ultrasonic Sensor → Servo Motor\
•	HC-SR04:\
o	VCC → 5V\
o	GND → GND\
o	Trig → D9\
o	Echo → D10\
Servo:\
•	Signal → D6\
•	VCC → 5V\
•	GND → GND

3. **Photoresistor → DC Motor via**\
•	Voltage divider:\
o	Photoresistor + 10kΩ between 5V and GND\
o	Junction → A0\
DC Motor:\
•	Powered via N-channel MOSFET (e.g., IRF540N)\
•	Gate → D5\
•	Drain → Motor GND\
•	Source → Battery GND\
•	Flyback diode across motor terminals

[**Sensor-Actuator.ino**](https://github.com/sapnajohn01/Robotics/blob/main/sensor-actuator.ino)

✅ **Testing Strategy**\
1.	Subsystem 1: Move hand near ultrasonic sensor → Servo should rotate accordingly.\
2.	Subsystem 2: Vary light intensity → DC motor speed should change.\
3.	Use multimeter to verify:\
o	Sensor voltages\
o	MOSFET gate switching\
o	Servo signal pulses

🧪 **Final Integration**\
Once both subsystems work independently:\
•	Mount components securely\
•	Label wires and pins\
•	Add LED indicators for system status (optional)\
•	Document wiring and code for reproducibility
