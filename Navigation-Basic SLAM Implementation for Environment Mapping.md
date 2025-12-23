Assignment 5: Basic SLAM Implementation for Environment Mapping

🛠 Core Components of the SLAM System\
1. Sensors & Odometry\
•	Distance sensors: Ultrasonic or IR sensors mounted on a servo (rotational) or multiple fixed sensors around the robot.\
•	Odometry: Wheel encoders (preferred) or timed movement estimates if encoders aren’t available.\
•	Noise handling: Apply simple filtering (moving average or median filter) to sensor readings.\
2. Occupancy Grid Mapping\
•	Represent the environment as a 2D grid (e.g., 100×100 cells).\
•	Each cell stores a probability of being occupied.\
•	Update rule:\
o	If sensor detects obstacle at distance d in direction θ, mark the corresponding cell as “occupied” with higher probability.\
o	Cells along the ray before the obstacle are updated as “free.”\
3. Position Estimation\
•	Start at (0,0) with heading 0°.\
•	Update position using odometry:\
o	x += Δd * cos(θ)\
o	y += Δd * sin(θ)\
o	θ += Δθ (rotation from encoders or timed turns).\
•	Accumulate error, but keep consistent relative positioning.\
4. Exploration Pattern\
•	Wall-following: Robot hugs walls and scans surroundings.\
•	Systematic coverage: Spiral or boustrophedon (lawnmower) pattern for open areas.\
•	Ensure robot rotates periodically to scan 360°.\
📊 Algorithm Flow\
1.	Initialization\
o	Set occupancy grid to unknown (0.5 probability).\
o	Robot starts at (0,0).\
2.	Loop\
o	Move forward a small step.\
o	Record odometry update.\
o	Rotate sensor (or read from fixed sensors).\
o	For each sensor reading:\
	Convert polar coordinates (d, θ) to global (x,y) using current robot pose.\
	Update occupancy grid.\
o	If obstacle detected ahead → turn left/right (wall-following).\
o	Continue until area is covered.\
3.	Map Output\
o	Visualize occupancy grid (e.g., matplotlib heatmap).\
o	Compare against known room layout.\
✅ Evaluation Checklist\
•	Accuracy: Compare generated occupancy grid with actual room layout.\
•	Consistency: Robot’s estimated path should roughly match its true path.\
•	Coverage: Ensure exploration pattern visits most of the room.\
•	Noise handling: Sensor filtering prevents spurious obstacles.\
•	Efficiency: Wall-following ensures systematic coverage.

