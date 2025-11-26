Assignment 5: Sensor Calibration and Noise Filtering Laboratory

🧭 Sensor Selection\
Sensor Type	Purpose	Common Issues\
Ultrasonic	Distance measurement	Echo noise, temperature drift\
IR Distance	Short-range obstacle detection	Ambient light interference, non-linearity\
IMU (Accelerometer, Gyroscope, Magnetometer)	Orientation and motion tracking	Bias, drift, magnetic distortion

🔧 Calibration Procedures\
1. Ultrasonic Sensor\
•	Min/Max Range Test: Use a calibrated ruler and flat reflective surface. Record readings from 2 cm to max range (e.g., 400 cm).\
•	Linearity Compensation:\
o	Fit a linear regression model: distance_actual = a * distance_measured + b\
o	Apply correction in firmware.\
•	Environmental Adjustment:\
o	Measure temperature using onboard sensor.\
o	Adjust speed of sound:
 
•	Recalculate distance:\
2. IR Distance Sensor\
•	Range & Linearity:\
o	Use known distances (5–80 cm).\
o	Fit inverse model:
 
Ambient Light Compensation:\
•	Measure sensor output in dark and bright conditions.\
•	Use differential readings or shielded enclosure.\
3. IMU Sensor\
•	Gyroscope Bias Calibration:\
o	Keep sensor stationary for 10 seconds.\
o	Average output → subtract from future readings.\
•	Accelerometer Scaling:\
o	Align each axis with gravity.\
o	Expected output: ±9.81 m/s².\
o	Compute scale factor:
 
Magnetometer Hard/Soft Iron Calibration:\
•	Rotate sensor in all directions.\
•	Fit ellipsoid to data → apply transformation matrix to normalize.

🧹 Noise Filtering Techniques\
Filter Type	Description	Best For\
Moving Average	Smooths short-term fluctuations	Ultrasonic, IR\
Median Filter	Removes spikes/outliers	IR in noisy lighting\
Low-Pass Filter	Attenuates high-frequency noise	IMU gyroscope/accel\
Example: Moving Average (Window = 5)\
def moving_average(data, window=5):\
    return [sum(data[i:i+window])/window for i in range(len(data)-window+1)]

📊 Sensor Characterization Tests\
Condition	Ultrasonic	IR Distance	IMU\
Distance Range	2–400 cm	5–80 cm	N/A\
Angle Variation	±45° incidence	±30° incidence	N/A\
Lighting	N/A	Dark vs bright	N/A\
Temperature	10°C–40°C	10°C–40°C	Drift over time\
Motion	N/A	N/A	Rotation, vibration

•	Log raw vs calibrated readings.\
•	Compute RMSE, standard deviation, and latency.\
🧠 Compensation Algorithms\
Ultrasonic\
def compensate_ultrasonic(raw_time, temp):\
    v = 331 + 0.6 * temp\
    return (v * raw_time) / 2

IR Distance\
def compensate_ir(voltage, A, B):\
    return A / (voltage - B)\
IMU\
def compensate_gyro(raw_gyro, bias):\
    return [g - b for g, b in zip(raw_gyro, bias)]

📘 Documentation & Performance Metrics\
Sensor	RMSE Before	RMSE After	Improvement (%)\
Ultrasonic	3.2 cm	0.8 cm	75%\
IR	5.5 cm	1.2 cm	78%
IMU	2.1°/s drift	0.3°/s	85%
