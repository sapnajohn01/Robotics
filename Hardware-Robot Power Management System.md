**Assignment 3: Robot Power Management System**

Here's a complete breakdown of the power management system for your mobile robot, combining hardware design and Arduino code to meet all your objectives.

⚡ **System Overview**\
This system includes:\
•	Battery voltage monitoring via a voltage divider\
•	Low-voltage cutoff using MOSFETs\
•	Independent power control for motors and sensors\
•	Visual LED indicators for battery status

🔧 **Hardware Design**
1. Voltage Divider Circuit\
To safely read 9V–12V battery levels on an Arduino analog pin (max 5V), use a voltage divider:\
Target: Scale 12V down to ≤5V Formula:
 
Recommended Resistors:\
•	R1 = 10kΩ\
•	R2 = 4.7kΩ\
•	Max input:
 
Connect:\
•	Battery + to R1\
•	R1 to R2\
•	R2 to GND\
•	Junction of R1/R2 to Arduino A0

**2. MOSFET Power Control**\
Use N-channel MOSFETs (e.g., IRF540N) to switch power to:\
•	Motors\
•	Sensors\
Connections:\
•	Drain → Component GND\
•	Source → Battery GND\
•	Gate → Arduino digital pin (via 220Ω resistor)\
Add flyback diodes across motor terminals for protection.

**4. LED Indicators**\
Use 3 LEDs:\
•	Green → Battery OK\
•	Yellow → Warning (e.g., <8V)\
•	Red → Critical (<7V)\
Connect each LED with a 220Ω resistor to digital pins.

[**Power**](https://github.com/sapnajohn01/Robotics/blob/main/Power.ino)

🧪 **Test & Validation**\
•	Simulate voltage drop using a variable power supply or battery drain.\
•	Confirm LED status and MOSFET switching behavior.\
•	Use Serial.println() to monitor voltage readings.
