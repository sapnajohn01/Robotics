Assignment 5: Debugging and Optimization Challenge

•	Sensor simulation (ultrasonic + IR)\
•	Decision logic\
•	Motor control abstraction\
•	Debug output toggle\
•	Optimization-ready structure

🤖 Python Maze Navigation Skeleton\
import time\
import random\
# === Debug Flag ===
DEBUG = True\
def debug(msg):\
    if DEBUG:\
        print(f"[DEBUG] {msg}")

# === Simulated Sensor Readings ===
def read_ultrasonic():\
    # Simulate distance in cm\
    return random.randint(5, 100)

def read_ir():\
    # Simulate analog IR value\
    return random.randint(200, 800)

# === Motor Control Abstraction ===
def move_forward():\
    debug("Motors: Moving Forward")

def turn_left():\
    debug("Motors: Turning Left")

def turn_right():\
    debug("Motors: Turning Right")

def stop():\
    debug("Motors: Stopping")

# === Decision Logic ===
def decide_action(front, left, right):\
    debug(f"Sensor Readings - Front: {front}cm | Left: {left}cm | Right: {right}cm")\
    if front < 15:\
        if left > right:\
            return "LEFT"\
        else:\
            return "RIGHT"\
    elif front < 30:\
        return "STOP"\
    else:\
        return "FORWARD"

# === Main Loop ===
def main():\
    while True:\
        front = read_ultrasonic()\
        left = read_ultrasonic()\
        right = read_ultrasonic()

        action = decide_action(front, left, right)\
        debug(f"Decision: {action}")

        if action == "FORWARD":\
            move_forward()\
        elif action == "LEFT":\
            turn_left()\
        elif action == "RIGHT":\
            turn_right()\
        elif action == "STOP":\
            stop()\
        time.sleep(1)

if __name__ == "__main__":\
    main()

🧪 Testing Protocol\
Scenario	Sensor Inputs (cm)	Expected Action\
Clear path	Front: 50, Left: 40, Right: 45	FORWARD\
Wall ahead	Front: 10, Left: 30, Right: 20	LEFT\
Dead end	Front: 10, Left: 10, Right: 10	RIGHT or STOP\
Narrow corridor	Front: 25, Left: 15, Right: 15	STOP

🛠️ Raspberry Pi Maze Navigation with Real Sensors\
🔌 Hardware Setup\
Component	Purpose	GPIO Pins Example\
HC-SR04	Ultrasonic distance sensing	TRIG: GPIO23, ECHO: GPIO24\
IR Sensors	Wall detection	GPIO17, GPIO27\
Motor Driver (L298N)	Motor control	IN1–IN4, ENA/ENB

🧠 Python Code with GPIO Integration\
import RPi.GPIO as GPIO\
import time

# === GPIO Setup ===\
GPIO.setmode(GPIO.BCM)\
TRIG = 23\
ECHO = 24\
IR_LEFT = 17\
IR_RIGHT = 27\
MOTOR_PINS = [5, 6, 13, 19]  # IN1–IN4

for pin in [TRIG, ECHO, IR_LEFT, IR_RIGHT] + MOTOR_PINS:\
    GPIO.setup(pin, GPIO.OUT if pin in MOTOR_PINS + [TRIG] else GPIO.IN)

# === Debug Flag ===
DEBUG = True\
def debug(msg):\
    if DEBUG:\
        print(f"[DEBUG] {msg}")

# === Sensor Functions ===
def read_ultrasonic():\
    GPIO.output(TRIG, False)\
    time.sleep(0.05)\
    GPIO.output(TRIG, True)\
    time.sleep(0.00001)\
    GPIO.output(TRIG, False)

    while GPIO.input(ECHO) == 0:\
        pulse_start = time.time()\
    while GPIO.input(ECHO) == 1:\
        pulse_end = time.time()

    duration = pulse_end - pulse_start\
    distance = duration * 17150\
    return round(distance, 2)

def read_ir(pin):\
    return GPIO.input(pin)

# === Motor Control ===
def move_forward():\
    GPIO.output(MOTOR_PINS, (1, 0, 1, 0))\
    debug("Motors: Forward")

def turn_left():\
    GPIO.output(MOTOR_PINS, (0, 1, 1, 0))\
    debug("Motors: Left")

def turn_right():\
    GPIO.output(MOTOR_PINS, (1, 0, 0, 1))\
    debug("Motors: Right")

def stop():\
    GPIO.output(MOTOR_PINS, (0, 0, 0, 0))\
    debug("Motors: Stop")

# === Decision Logic ===
def decide_action(front, ir_left, ir_right):\
    debug(f"Front: {front}cm | IR Left: {ir_left} | IR Right: {ir_right}")\
    if front < 15:\
        return "LEFT" if ir_left == 0 else "RIGHT"\
    elif front < 30:\
        return "STOP"\
    else:\
        return "FORWARD"

# === Main Loop ===
try:\
    while True:\
        front = read_ultrasonic()\
        ir_left = read_ir(IR_LEFT)\
        ir_right = read_ir(IR_RIGHT)

        action = decide_action(front, ir_left, ir_right)

        if action == "FORWARD":\
            move_forward()\
        elif action == "LEFT":\
            turn_left()\
        elif action == "RIGHT":\
            turn_right()\
        elif action == "STOP":\
            stop()

        time.sleep(0.5)

except KeyboardInterrupt:\
    GPIO.cleanup()\
    print("Program terminated.")

🧪 Testing Protocol\
•	Dry Run: Use mock sensor values to test logic flow.\
•	Live Test: Place robot in a simple maze with walls and observe behavior.\
•	Diagnostics: Enable DEBUG = True to trace decisions and sensor values.

🧩 Optional Add-ons\
•	PID control for smoother turns\
•	Kalman filter for noisy sensor data\
•	Dashboard via Flask for remote monitoring\
•	Simulation in Gazebo with ROS bridge


