Assignment 4: IMU-Based Orientation and Navigation System

🛠️ Phase 1: IMU Integration and Communication\
✅ Hardware Setup\
•	IMU Module: Use MPU6050 or MPU9250 (includes magnetometer).\
•	Connection:\
o	I2C: Connect SDA/SCL to microcontroller (e.g., Arduino, Raspberry Pi).\
o	Ensure pull-up resistors (4.7kΩ typical) on SDA/SCL lines.\
o	Stable 3.3V or 5V power depending on IMU specs.

✅ Microcontroller Configuration\
•	Initialize I2C/SPI communication.\
•	Use libraries like Wire.h (Arduino) or smbus (Python) for data access.\
•	Confirm device address (e.g., 0x68 for MPU6050) and test with basic read/write.

🧪 Phase 2: Sensor Calibration\
🔧 Gyroscope Bias Calibration\
•	Keep IMU stationary for 5–10 seconds.\
•	Average multiple readings to compute bias:\
🔧 Accelerometer Calibration\
•	Use known 🧲 Magnetometer Calibration (if available)\
•	Perform soft and hard iron calibration using figure-eight motion.\
•	Normalize readings to unit vector for heading estimation.\
•	🔄 Phase 3: Sensor Fusion for Orientation\
•	🧮 Complementary Filter (Lightweight)\
•  α ≈ 0.98 for smooth fusion.\
•  Use atan2(accel_y, accel_z) for pitch/roll estimation.

📊 Kalman Filter (Advanced)\
•	Implement 1D or 3D Kalman filter for roll, pitch, yaw.\
•	Models:\
o	State: angle, angular velocity.\
o	Measurement: accelerometer-derived angle.\
o	Prediction: gyro integration.\
🧭 Phase 4: Orientation Tracking and Heading Maintenance\
🧠 Heading Estimation\
•	Use fused yaw angle (gyro + magnetometer).\
•	Maintain heading even during vibration or slippage.

🔁 Drift Compensation\
•	Periodically re-align heading using magnetometer or known landmarks.\
•	Apply low-pass filtering to suppress noise.\
🚗 Phase 5: Navigation System Using IMU

➡️ Straight-Line Travel\
•	Maintain constant heading angle.\
•	Compare current orientation to desired heading

↩️ Accurate Turns\
•	Rotate robot until yaw angle matches target.\
•	Use PID controller for smooth turning.

🔄 Recovery After Disturbance\
•	Detect sudden orientation change.

🧪 Testing & Evaluation\
Criteria	Validation Method\
IMU Communication	Serial monitor output of raw sensor data\
Calibration Accuracy	Compare static readings to expected values\
Orientation Stability	Plot fused angles over time during motion\
Heading Maintenance	Track deviation from straight path\
Drift Handling	Long-duration test with periodic re-alignment\
Navigation Integration	Obstacle course with turns and recovery scenarios
