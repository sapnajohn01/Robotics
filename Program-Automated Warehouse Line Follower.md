Assignment 3: Automated Warehouse Line Follower

🧰 Hardware Assumptions\
•	3 IR sensors: Left, Center, Right (digital output)\
•	2 DC motors: Controlled via L298N or similar driver\
•	Raspberry Pi: Running Python with RPi.GPIO or gpiozero\
•	Track: Black line on white surface

🧠 Python Logic Overview\
1. Setup and Imports\
import RPi.GPIO as GPIO\
import time

# Sensor pins\
LEFT = 17\
CENTER = 27\
RIGHT = 22

# Motor pins\
LEFT_MOTOR_FORWARD = 5\
LEFT_MOTOR_BACKWARD = 6\
RIGHT_MOTOR_FORWARD = 13\
RIGHT_MOTOR_BACKWARD = 19

GPIO.setmode(GPIO.BCM)\
GPIO.setup([LEFT, CENTER, RIGHT], GPIO.IN)\
GPIO.setup([LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD], GPIO.OUT)

2. Motor Control Functions\
def move_forward():\
    GPIO.output(LEFT_MOTOR_FORWARD, True)\
    GPIO.output(LEFT_MOTOR_BACKWARD, False)\
    GPIO.output(RIGHT_MOTOR_FORWARD, True)\
    GPIO.output(RIGHT_MOTOR_BACKWARD, False)

def turn_left():\
    GPIO.output(LEFT_MOTOR_FORWARD, False)\
    GPIO.output(LEFT_MOTOR_BACKWARD, True)\
    GPIO.output(RIGHT_MOTOR_FORWARD, True)\
    GPIO.output(RIGHT_MOTOR_BACKWARD, False)

def turn_right():\
    GPIO.output(LEFT_MOTOR_FORWARD, True)\
    GPIO.output(LEFT_MOTOR_BACKWARD, False)\
    GPIO.output(RIGHT_MOTOR_FORWARD, False)\
    GPIO.output(RIGHT_MOTOR_BACKWARD, True)

def stop():\
    GPIO.output([LEFT_MOTOR_FORWARD, LEFT_MOTOR_BACKWARD, RIGHT_MOTOR_FORWARD, RIGHT_MOTOR_BACKWARD], False)\
3. Sensor Reading and Line Following\
def read_sensors():\
    return GPIO.input(LEFT), GPIO.input(CENTER), GPIO.input(RIGHT)

def follow_line():\
    left, center, right = read_sensors()\
    if center == 0 and left == 1 and right == 1:\
        move_forward()\
    elif left == 0:\
        turn_left()\
    elif right == 0:\
        turn_right()\
    else:\
        stop()

4. Intersection Detection and Decision Logic\
def is_intersection():\
    left, center, right = read_sensors()\
    return left == 0 and center == 0 and right == 0\
def decide_turn(destination_code):\
    if destination_code == 'A':\
        turn_left()\
    elif destination_code == 'B':\
        move_forward()\
    elif destination_code == 'C':\
        turn_right()\
    time.sleep(1)  # Allow turn to complete

5. Main Loop with State Reporting\
destination_code = 'B'  # Example: 'A' = left, 'B' = straight, 'C' = right\
try:\
    while True:\
        if is_intersection():\
            stop()\
            print("Intersection detected")\
            print(f"Sensors: {read_sensors()} | Decision: {destination_code}")\
            decide_turn(destination_code)\
        else:\
            follow_line()\
        time.sleep(0.1)\
except KeyboardInterrupt:\
    GPIO.cleanup()

Test & Debug Tips\
•  Use print(read_sensors()) to calibrate sensor thresholds.\
•  Test each motor direction independently before full integration.\
•  Validate intersection logic with a triple-black patch on your track.
