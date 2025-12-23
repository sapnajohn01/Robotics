Assignment 2: Obstacle Avoidance System for Indoor Navigation

🛠 Hardware Setup\
•	Ultrasonic sensors: At least two mounted at the front (left and right angles). Optionally add side sensors for better coverage.\
•	Microcontroller/board: Arduino, Raspberry Pi, or similar.\
•	Motors & motor driver: Differential drive (two wheels + caster) works well for smooth turning.\
•	Power supply: Battery pack sized for your motors and sensors.\
⚙️ Software Logic (High-Level Flow)\
1.	Forward Motion\
o	Robot moves forward while continuously reading distance from ultrasonic sensors.\
o	Define a safety threshold (e.g., 30 cm).\
2.	Obstacle Detection\
o	If either sensor detects an obstacle < threshold:\
	Stop motors immediately.\
	Read both left and right sensor values.\
3.	Decision Making\
o	Compare left vs. right distances.\
o	Choose the direction with more clearance.\
o	If both sides blocked, back up slightly and reassess.\
4.	Avoidance Maneuver\
o	Execute a smooth turn toward the chosen direction.\
o	Move forward until the obstacle is cleared.\
o	Gradually steer back to the original heading.\
5.	Resume Path\
o	Once clear, realign to the original forward trajectory.\
o	Continue toward destination.\
🚦 Testing Strategy\
•	Place obstacles of different sizes (boxes, chairs, walls).\
•	Vary angles (straight ahead, diagonal).\
•	Test in cluttered environments (multiple obstacles).\
•	Observe:\
o	No collisions.\
o	Smooth turns (no jerky stops).\
o	Robot resumes original heading after avoidance.\
✅ Evaluation Checklist\
•	Detection reliability: Sensors consistently trigger at ~30 cm.\
•	Avoidance logic: Robot chooses correct side and avoids collisions.\
•	Smoothness: Turns are gradual, not abrupt.\
•	Path resumption: Robot returns to original heading.\
•	Consistency: Works across different obstacle sizes and angles.
