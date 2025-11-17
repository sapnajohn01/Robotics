**Assignment 2: Feedforward Control for Precise Motor Positioning**

🧠 **Step 1: Analyze Robotic Arm Dynamics**\
**Dominant Forces**\
•	Gravitational Torque: Varies with arm angle and payload mass.\
•	Inertial Forces: Depend on angular acceleration and moment of inertia.

**Assumptions**\
•	Rigid links with known mass and length.\
•	Payload mass is variable but known.\
•	Joint friction is negligible or compensated separately.

📐 **Step 2: Mathematical Modeling**\
1-DOF Arm (for simplicity)\
Model a single rotary joint with a payload at the end.

**Gravitational Torque**\
•	 : mass of link + payload\
•	 : gravitational acceleration\
•	 : distance to center of mass\
•	 : joint angle

**Inertial Torque**\
•	 : moment of inertia\
•	 : angular acceleration\
Total Feedforward Torque

🧮 Step **3: Implement Feedforward Control**\
**Control Architecture**\
Desired Position → Feedforward (τ_ff) → Motor\
                 → PID Feedback (τ_fb) → Motor\

**Combined Control Signal**\
tau_total = tau_ff + tau_fb\
tau_total = tau_ff + tau_fb

**Python code (for simulation)**\
def feedforward_torque(theta, theta_ddot, m, l, I, g=9.81):\
    tau_g = m * g * l * np.cos(theta)\
    tau_i = I * theta_ddot\
    return tau_g + tau_i

🧪 **Step 4: Testing and Validation**\
**Test Conditions**\
•	Vary payload mass (e.g., 0.5 kg, 1 kg, 2 kg)\
•	Command positions: 30°, 60°, 90°\
•	Compare:\
o	Settling time\
o	Overshoot\
o	Steady-state error

**Evaluation Metrics**\
Payload	Target Angle	Settling Time (PID only)	Settling Time (PID + FF)	Overshoot	Steady-State Error\
1 kg	60°	1.2 s	0.8 s	5%	2°\
2 kg	90°	1.8 s	1.1 s	8%	3°
