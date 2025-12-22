Assignment 4: Maze Solving Robot Using Right-Hand Rule

🧭 Core Algorithm: Right-Hand Rule
•	Principle: At every intersection, the robot checks sensors in priority order:
1.	Right sensor → If clear, turn right.
2.	Front sensor → If clear, go straight.
3.	Left sensor → If clear, turn left.
4.	Else → Dead end → turn around (180°).
•	This guarantees eventual exit in a simply connected maze (no isolated loops).

🔧 Hardware Setup
•	Sensors:
o	Ultrasonic or IR sensors facing front, left, right.
o	Optional rear sensor for debugging/stuck detection.
•	Actuators:
o	Differential drive motors (left/right wheels).
o	Servo or stepper for precise turns.
•	Controller:
o	Arduino, ESP32, or Raspberry Pi for sensor fusion + decision logic.

⚙️ State Machine Design
Define robot states to keep navigation modular and auditable:
•	MOVE_FORWARD → Advance until obstacle detected.
•	TURN_RIGHT → Rotate 90° clockwise.
•	TURN_LEFT → Rotate 90° counterclockwise.
•	TURN_AROUND → Rotate 180° at dead ends.
•	ERROR_RECOVERY → Back up slightly, recheck sensors if stuck.
Each state transitions based on sensor inputs:
•	Example: From MOVE_FORWARD, if right sensor clears → transition to TURN_RIGHT.

🛠️ Decision-Making Logic
•	Sensor thresholds:
o	Define “wall detected” as distance < 15 cm (adjustable).
•	Priority logic:
o	Right > Front > Left > Turn Around.
•	Loop detection:
o	Optional: track visited intersections with simple counter or breadcrumbs (not required for basic right-hand rule, but improves efficiency).

🚨 Error Handling
•	Stuck detection:
o	If all sensors blocked but robot not moving → back up 10 cm, retry.
•	Sensor noise:
o	Apply median filtering or moving average to avoid false positives.
•	Motor slip:
o	Add encoder feedback to ensure accurate turns.

🧪 Testing Strategy
1.	Simple corridor maze → Verify straight-line navigation.
2.	Single intersection maze → Confirm right-hand priority.
3.	Dead-end maze → Test turn-around logic.
4.	Loop maze → Ensure eventual exit without infinite cycling.
5.	Complex maze with multiple branches → Measure completion time vs. optimal path.
   
📊 Evaluation Criteria Alignment
•	Navigation success: Robot exits all test mazes.
•	Correct algorithm: Always prioritizes right-hand turns.
•	Efficiency: Minimal unnecessary backtracking.
•	Reliability: Sensors consistently detect walls.
•	Performance: Completion time close to optimal path.
