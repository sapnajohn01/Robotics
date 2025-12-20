Assignment 1: Bluetooth-Controlled Robot for Warehouse Inventory

🔧 Hardware Setup/
🧩 Components/
•	Microcontroller: Arduino Uno/Nano/
•	Bluetooth Module: HC-05 or HC-06/
•	Motor Driver: L298N or L293D/
•	Chassis: 2WD or 4WD robot base/
•	Motors: DC gear motors/
•	Power Supply: 7.4V Li-ion battery (regulated to 5V for logic)/
•	Optional: Ultrasonic sensor for obstacle detection

🔌 Wiring Diagram/
HC-05/06 Pin	Arduino Pin	Notes/
VCC	5V	Use voltage divider if using HC-05 with 3.3V logic/
GND	GND	Common ground is essential/
TXD	RX (D10)*	Use SoftwareSerial for flexibility/
RXD	TX (D11)*	Use voltage divider (1kΩ + 2kΩ) to drop 5V to ~3.3V/
*Use SoftwareSerial on pins 10 (RX) and 11 (TX) to avoid conflict with USB serial.

📱 Mobile Interface/
Option 1: Bluetooth Terminal App/
•	Use apps like Serial Bluetooth Terminal (Android) or Bluetooth Serial Controller./
•	Send single-character commands: F, B, L, R, S./
Option 2: Custom App (Optional)/
•	Build a simple UI with buttons mapped to commands./
•	Use MIT App Inventor or Flutter with Bluetooth plugins.

🔁 Bidirectional Communication/
•	Robot sends status messages back (e.g., “Moving Forward”, “Stopped”)./
•	You can expand this to include battery level, obstacle alerts, etc.

📶 Range & Reliability Testing/
•	Test in a 10-meter radius with line-of-sight and obstructions./
•	Monitor for dropped packets or delayed responses./
•	Use Serial.println() for debugging and logging.

✅ Evaluation Checklist/
Criteria	Implementation/
Pairing	HC-05/06 paired via mobile Bluetooth settings/
Command Execution	All movement commands mapped and tested/
Feedback	Status messages sent back to mobile/
Range	Stable within 10 meters/
Code Quality	Modular, commented, and readable

🐍 Python for Bluetooth-Controlled Robot/
🔌 Option 1: Raspberry Pi + Python + HC-05/
If you're using a Raspberry Pi, Python can handle Bluetooth communication directly via the pyserial or bluetooth libraries./
Example: Listening for Commands via Serial Bluetooth
import serial

# Connect to HC-05 via serial (adjust port as needed)/
bt = serial.Serial('/dev/rfcomm0', baudrate=9600, timeout=1)/
while True:/
    if bt.in_waiting:/
        command = bt.readline().decode().strip()/
        print(f"Received: {command}")/
        if command == 'F':/
            print("Move Forward")/
        elif command == 'B':/
            print("Move Backward")/
        elif command == 'L':/
            print("Turn Left")/
        elif command == 'R':/
            print("Turn Right")/
        elif command == 'S':/
            print("Stop")/
        else:/
            print("Unknown Command")

You’ll need to pair the HC-05 with the Pi first using bluetoothctl and bind it to /dev/rfcomm0.
