Assignment 4: Finite State Machine for Security Robot

🧠 FSM Design Overview\
🎯 States\\
State	Behavior Description
PATROL	Follows a predefined path using line-following or waypoint navigation\
ALERT	Stops movement, activates warning lights/sound, logs incident\
INVESTIGATE	Slowly approaches detected object using ultrasonic or IR sensors\
RETURN_HOME	Navigates back to base using GPS, compass, or stored path

🔁 State Transition Logic\
Current State	Condition	Next State\
PATROL	Obstacle detected within threshold (e.g., < 50 cm)	ALERT\
ALERT	Timer expires (e.g., 5 seconds)	INVESTIGATE\
INVESTIGATE	Object confirmed or timeout	RETURN_HOME\
RETURN_HOME	Reached base	PATROL\
Any	Manual override	RETURN_HOME

🧠 FSM Architecture in Python\
📦 Setup: State Definitions and Transition Logic

from enum import Enum\
import time

class State(Enum):\
    PATROL = 1\
    ALERT = 2\
    INVESTIGATE = 3\
    RETURN_HOME = 4

class RobotFSM:\
    def __init__(self):\
        self.state = State.PATROL\
        self.state_start_time = time.time()

    def transition_to(self, new_state, reason):\
        print(f"\nTransitioning from {self.state.name} to {new_state.name} due to: {reason}")\
        self.state = new_state\
        self.state_start_time = time.time()

    def run(self):\
        while True:\
            if self.state == State.PATROL:\
                self.patrol()\
                if self.ultrasonic_distance() < 50:\
                    self.transition_to(State.ALERT, "Obstacle detected")

            elif self.state == State.ALERT:\
                self.alert()\
                if time.time() - self.state_start_time > 5:\
                    self.transition_to(State.INVESTIGATE, "Alert timeout")

            elif self.state == State.INVESTIGATE:\
                self.investigate()\
                if self.object_confirmed() or time.time() - self.state_start_time > 8:\
                    self.transition_to(State.RETURN_HOME, "Investigation complete or timeout")

            elif self.state == State.RETURN_HOME:\
                self.return_home()\
                if self.at_base():\
                    self.transition_to(State.PATROL, "Returned to base")

            if self.manual_override():\
                self.transition_to(State.RETURN_HOME, "Manual override")

            time.sleep(0.1)  # Loop delay for stability

🧩 State Behavior Functions\
    def patrol(self):\
        print("State: PATROL - Following path")\
        # Add motor control logic here

    def alert(self):\
        print("State: ALERT - Stopping and activating warning lights")\
        # Stop motors, blink LEDs

    def investigate(self):\
        print("State: INVESTIGATE - Approaching object cautiously")\
        # Slow movement toward object

    def return_home(self):\
        print("State: RETURN_HOME - Navigating to base")\
        # Use stored path or GPS

    # Sensor and control stubs\
    def ultrasonic_distance(self):\
        return 100  # Replace with actual sensor reading

    def object_confirmed(self):\
        return False  # Replace with object detection logic

    def at_base(self):\
        return False  # Replace with base detection logic

    def manual_override(self):\
        return False  # Replace with button or remote signal

🧪 Testing Strategy\
Simulate transitions by modifying sensor stubs or using mock inputs. For example:\
robot = RobotFSM()\
robot.run()

🔧 Optional Enhancements\
•	Integrate gpiozero or RPi.GPIO for real sensor/motor control\
•	Add logging to file for post-run analysis\
•	Use threading for asynchronous sensor monitoring\
•	Visualize FSM with graphviz or transitions library

Here’s a visual FSM diagram that illustrates the patrol robot’s behavior across its four states: PATROL, ALERT, INVESTIGATE, and RETURN_HOME. The transitions are triggered by sensor inputs, timeouts, or manual overrides.\
🔄 Finite State Machine Overview\
States and Transitions:

          +----------------+
          |                |
          |    PATROL      |
          |                |
          +--------+-------+
                   |
        Obstacle Detected (<50cm)
                   v
          +--------+-------+
          |                |
          |     ALERT      |
          |                |
          +--------+-------+
                   |
             Timeout (5s)
                   v
          +--------+-------+
          |                |
          |  INVESTIGATE   |
          |                |
          +--------+-------+
                   |
       Object Confirmed or Timeout
                   v
          +--------+-------+
          |                |
          |  RETURN_HOME   |
          |                |
          +--------+-------+
                   |
             Reached Base
                   v
          +--------+-------+
          |                |
          |    PATROL      |
          |                |
          +----------------+

🧪 Option 2: Test Case Matrix for Simulation\
Scenario	Initial State	Trigger	Expected State\
Obstacle detected	PATROL	Distance < 50cm	ALERT\
Timeout	ALERT	5s elapsed	INVESTIGATE\
Object confirmed	INVESTIGATE	Sensor flag	RETURN_HOME\
Timeout	INVESTIGATE	8s elapsed	RETURN_HOME\
Reached base	RETURN_HOME	Base proximity	PATROL\
Manual override	Any	Button press	RETURN_HOME


