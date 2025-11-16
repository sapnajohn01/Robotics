**Assignment 4: Closed-Loop vs Open-Loop Control Comparison**

Comparing open-loop and closed-loop control strategies for a cost-sensitive robot platform.\
🧪 **Experimental Scenario: Maintaining Constant Wheel Speed**\
🎯 **Task Definition**\
Maintain a constant wheel speed of 100 RPM using:\
•	Open-loop control: Fixed PWM signal to motor driver\
•	Closed-loop control: PID controller using encoder feedback

⚙️ **Control System Implementation**\
**Control Type	Description**\
Open-loop	PWM duty cycle calibrated for 100 RPM under ideal conditions\
Closed-loop	PID controller adjusts PWM based on encoder feedback to maintain 100 RPM

🧪 **Experimental Design**\
🔧 **Variables**\
•	Load variation: Add weights incrementally (0g, 100g, 200g)\
•	Surface friction: Test on smooth tile, carpet, and rubber mat\
•	Battery voltage: Test at 100%, 75%, and 50% charge

📊 **Metrics Collected**
•	Speed error (actual vs target RPM)\
•	Time to reach target speed\
•	Energy consumption (via current sensor)\
•	Repeatability across trials\
•	Disturbance rejection (response to sudden load change)

📈 **Results Summary**\
Condition	Open-loop Avg Error	Closed-loop Avg Error	Energy Use (mAh)	Repeatability	Disturbance Rejection\
Ideal (no load)	±5 RPM	±0.5 RPM	20	Medium	Poor\
200g load	±15 RPM	±1 RPM	25	Low	Good\
Carpet surface	±10 RPM	±0.8 RPM	22	Low	Good\
50% battery voltage	±18 RPM	±2 RPM	30	Low	Excellent
