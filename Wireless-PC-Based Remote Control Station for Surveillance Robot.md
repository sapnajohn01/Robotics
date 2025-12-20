Assignment 3: PC-Based Remote Control Station for Surveillance Robot

🔌 Step 1: Serial Communication Setup\
Microcontroller side (Arduino/ESP32/etc.):\
Configure Serial.begin(9600) or higher baud rate (e.g., 115200 for faster data).\
Define a packet structure: e.g., CMD:FORWARD for commands, DATA:ULTRASONIC=120,TEMP=25 for sensor data.\
Ensure newline (\n) or delimiter (;) at the end of each packet for parsing.\
PC side (Python with pySerial):

python\
import serial\
ser = serial.Serial('COM3', 9600, timeout=1)  # Adjust COM port & baud rate\
ser.flush()\
🎮 Step 2: Sending Movement Commands\
Create functions to send commands:

python\
def send_command(cmd):\
    ser.write(f"CMD:{cmd}\n".encode('utf-8'))\
Example usage:

python\
send_command("FORWARD")\
send_command("STOP")\
📡 Step 3: Receiving Sensor Data\
Continuously read incoming data:

python\
def read_data():\
    if ser.in_waiting > 0:\
        line = ser.readline().decode('utf-8').strip()\
        if line.startswith("DATA:"):\
            return line\
    return None\
Parse sensor values:

python\
data = read_data()\
if data:\
    # Example: DATA:ULTRASONIC=120,TEMP=25\
    parts = data.replace("DATA:", "").split(",")\
    sensor_dict = {kv.split("=")[0]: kv.split("=")[1] for kv in parts}\
    print(sensor_dict)
    
🖥️ Step 4: GUI Dashboard (Tkinter)\
Build a simple interface with buttons + labels:

python\
import tkinter as tk

root = tk.Tk()\
root.title("Surveillance Robot Dashboard")

# Sensor labels\
ultrasonic_label = tk.Label(root, text="Ultrasonic: ---")\
ultrasonic_label.pack()\
temp_label = tk.Label(root, text="Temperature: ---")\
temp_label.pack()

# Command buttons\
tk.Button(root, text="Forward", command=lambda: send_command("FORWARD")).pack()\
tk.Button(root, text="Backward", command=lambda: send_command("BACKWARD")).pack()\
tk.Button(root, text="Left", command=lambda: send_command("LEFT")).pack()\
tk.Button(root, text="Right", command=lambda: send_command("RIGHT")).pack()\
tk.Button(root, text="Stop", command=lambda: send_command("STOP")).pack()

# Update loop\
def update_data():\
    data = read_data()\
    if data:\
        sensor_dict = {kv.split("=")[0]: kv.split("=")[1] for kv in data.replace("DATA:", "").split(",")}\
        ultrasonic_label.config(text=f"Ultrasonic: {sensor_dict.get('ULTRASONIC', '---')}")\
        temp_label.config(text=f"Temperature: {sensor_dict.get('TEMP', '---')}")\
    root.after(100, update_data)

update_data()\
root.mainloop()

✅ Testing & Evaluation\
Stable communication: Test with continuous sensor streaming at different baud rates.\
Responsive control: Verify robot reacts instantly to button presses.\
Real-time display: Sensor values should update within ~100ms.\
UI clarity: Labels should clearly show sensor states; buttons should be intuitive.\
Error handling: Add try/except around serial reads/writes to handle disconnections gracefully.

This setup gives you a bidirectional communication loop:\
PC → Robot (movement commands)\
Robot → PC (sensor data)
