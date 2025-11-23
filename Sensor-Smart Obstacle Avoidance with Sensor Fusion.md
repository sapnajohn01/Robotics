Assignment 3: Smart Obstacle Avoidance with Sensor Fusion
Here's a structured roadmap to help you design and implement a robust autonomous home-assistance robot with intelligent obstacle avoidance:

🧠 System Architecture Overview
🎯 Sensor Suite Integration
•	Ultrasonic Sensors:
o	Mount at 0°, ±45°, ±90° angles for frontal and lateral coverage.
o	Use foam or angled mounts to reduce cross-talk.
o	Time-division multiplexing to avoid echo interference.
•	IR Sensors:
o	Place near the base for detecting small or close-range objects.
o	Ideal for low-profile clutter like toys, cables, or thresholds.

Optional Add-ons:
•	IMU for orientation and drift correction.
•	LiDAR or depth camera (if budget allows) for richer spatial mapping.
•	Bumper switches as fail-safe for physical contact detection.
🔄 Sensor Fusion Strategy
📊 Weighted Fusion Algorithm
•	Normalize sensor readings to a common scale (e.g., distance in cm).
•	Assign dynamic weights based on:
o	Distance range: IR for <20 cm, ultrasonic for 20–200 cm.
o	Environmental factors: IR struggles with reflective surfaces; ultrasonic with soft materials

Use a confidence score per sensor:
fused_distance = (w_ir * d_ir + w_ultra * d_ultra) / (w_ir + w_ultra)
🧩 Conflict Resolution
•	If sensors disagree significantly:
o	Use historical data to validate.
o	Prioritize sensor with higher confidence in current context.
o	Flag anomaly for cautious behavior (e.g., slow down, re-scan).
🗺️ Obstacle Mapping
🧠 Local Map Construction
•	Maintain a 2D grid or occupancy map centered on the robot.
•	Update with fused sensor data:
o	Mark cells as occupied, free, or unknown.
o	Use decay function to remove stale data.
🧭 Position Tracking
•	Combine wheel encoders + IMU for dead reckoning.
•	Optional: SLAM if using LiDAR or depth camera.
🚗 Intelligent Avoidance Logic
🧠 Decision Tree
1.	Obstacle detected:
o	Classify: wall, furniture, small object.
o	Estimate size and distance.
2.	Trajectory analysis:
o	Predict collision based on current velocity and heading.
3.	Path planning:
o	Use reactive methods (e.g., Bug algorithm, VFH) or local A*.
o	Prioritize minimal deviation from goal.

🕹️ Behavior Modulation
•	Slow down near dense clutter.
•	Pause and scan if uncertain.
•	Re-route if blocked persistently.
🧪 Evaluation Checklist
Criteria	Implementation Notes
✅ Sensor Integration	Ultrasonic + IR + optional LiDAR
✅ Sensor Fusion	Weighted algorithm with confidence scores
✅ Obstacle Mapping	Real-time occupancy grid
✅ Avoidance Behavior	Dynamic path planning with classification
✅ Fault Handling	Sensor anomaly detection + fallback logic
✅ Smooth Navigation	Adaptive speed + predictive steering
