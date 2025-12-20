Assignment 2: Wi-Fi Enabled Environmental Monitoring Robot

🐍 MicroPython-Based Greenhouse Monitor/
🔧 Hardware Setup/
•	ESP8266 or ESP32 flashed with MicroPython firmware/
•	DHT11 or DHT22 sensor/
•	Wi-Fi access/
•	USB cable + Thonny IDE or uPyCraft IDE

🧠 Step 1: Flash MicroPython Firmware/
Use esptool.py to flash MicroPython:/
esptool.py --port /dev/ttyUSB0 erase_flash/
esptool.py --port /dev/ttyUSB0 write_flash -fm dio -fs 4MB 0x00000 esp8266-xxxx.bin

📦 Step 2: Install Required Modules/
Upload these to your board:/
•	dht.py (comes with MicroPython)/
•	urequests.py (for HTTP POST)

🧪 Step 3: Python Code (Non-blocking with utime)/
import network/
import urequests/
import dht/
import machine/
import utime

# Wi-Fi credentials/
SSID = 'your_ssid'/
PASSWORD = 'your_password'

# Connect to Wi-Fi/
station = network.WLAN(network.STA_IF)/
station.active(True)/
station.connect(SSID, PASSWORD)

while not station.isconnected():/
    utime.sleep(1)

print("Connected to Wi-Fi")/

# Sensor setup/
sensor = dht.DHT22(machine.Pin(4))  # Use Pin 2 for ESP8266 if needed

# Timing/
last_sent = 0/
interval = 30  # seconds

def send_data():/
    try:/
        sensor.measure()/
        temp = sensor.temperature()/
        hum = sensor.humidity()/
        payload = {"temperature": temp, "humidity": hum}/
        response = urequests.post("http://httpbin.org/post", json=payload)/
        print("Data sent:", response.text)/
        response.close()/
    except Exception as e:/
        print("Error:", e)

# Main loop/
while True:/
    current = utime.time()/
    if current - last_sent >= interval:/
        send_data()/
        last_sent = current/
    # Robot mobility or other tasks can run here

✅ Key Features/
•	Non-blocking loop using utime.time() for periodic execution/
•	HTTP POST with JSON payload/
•	Error handling for sensor and network issues/
•	Modular structure for easy integration into robot FSM

🧪 Testing Tips/
•	Use httpbin.org/post to inspect payloads/
•	Monitor serial output for timing and errors/
•	Simulate robot movement in parallel to confirm non-blocking behaviour
