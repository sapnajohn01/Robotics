Assignment 5: Real-World Control Challenge: Line Following with Disturbance Rejection

🧠 Phase 1: Basic Line-Following with Proportional Control\
🔧 Hardware Setup\
•	Sensors: Use 5–8 IR reflectance sensors (e.g., QTR or TCRT5000) arranged in a line.\
•	Microcontroller: Arduino or Raspberry Pi with real-time capabilities.\
•	Motors: Differential drive with encoders for feedback.

⚙️ Control Logic\
int error = weighted_average(sensor_values) - center_position;\
int motor_adjustment = Kp * error;\
left_motor_speed = base_speed - motor_adjustment;\
right_motor_speed = base_speed + motor_adjustment;\
•  Kp: Proportional gain tuned for responsiveness.\
•  Weighted average: Calculates the line position from sensor array.

🌪️ Phase 2: Introduce Real-World Challenges\
🧪 Environmental Variations\
•	Lighting: Use variable lighting (sunlight, shadows, flickering LEDs).\
•	Surface: Alternate between matte, glossy, and textured surfaces.\
•	Disturbances: Apply gentle bumps or nudges mid-course.

🛡️ Phase 3: Robust Control Enhancements\
🔍 Sensor Filtering\
•	Median filter or moving average to smooth noisy sensor readings.\
•	Normalize sensor values to account for reflectivity changes.

📈 Adaptive Control Gains\
•	Dynamically adjust Kp based on:\
o	Speed\
o	Sensor confidence\
o	Environmental feedback

🧭 Disturbance Observer\
•	Use an Extended State Observer (ESO) or Active Disturbance Rejection Control (ADRC) to estimate and reject external forces.\
🧠 PID or Fuzzy Logic Upgrade\
•	Add Integral and Derivative terms for better stability.\
•	Or implement Fuzzy Logic to adapt control based on sensor confidence and deviation.

🧪 Phase 4: Testing & Metrics\
🧭 Test Course Design\
•	Include:\
o	Straight paths\
o	Sharp curves\
o	Intersections\
o	Bumpy zones\
o	Reflective patches

•	📊 Performance Metrics\
Metric	Description\
Completion Time	Time to finish course\
Deviation from Center	Average lateral error from line\
Recovery Time	Time to re-center after disturbance\
Sensor Confidence	% of time sensors detect line accurately\
Stability Index	Variance in motor speed and heading

🔁 Phase 5: Iterative Optimization\
•	Log sensor data and motor commands.\
•	Visualize trajectory and error over time.\
•	Tune gains and filtering thresholds.\
•	Test across multiple lighting and surface setups.
