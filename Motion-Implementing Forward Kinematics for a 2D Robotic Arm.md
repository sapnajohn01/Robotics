Assignment 2: Implementing Forward Kinematics for a 2D Robotic Arm

🧠 Step 1: Define the Coordinate System\
•	Base Frame: Origin at the shoulder joint (0, 0)\
•	Link Definitions:\
o	Link 1: Length = L1, angle = θ1 (relative to x-axis)\
o	Link 2: Length = L2, angle = θ2 (relative to Link 1)

📐 Step 2: Derive Forward Kinematics Equations\
Using trigonometry:\
math\
x = L1 * cos(θ1) + L2 * cos(θ1 + θ2)\
y = L1 * sin(θ1) + L2 * sin(θ1 + θ2)\
These give the end-effector position (x, y) in the 2D plane.

💻 Step 3: Implement in Python\
Here’s a clean Python implementation using numpy and matplotlib:\
python\
import numpy as np\
import matplotlib.pyplot as plt\
from matplotlib.widgets import Slider

# Forward kinematics function
def forward_kinematics(theta1, theta2, L1=1.0, L2=1.0):\
    x1 = L1 * np.cos(theta1)\
    y1 = L1 * np.sin(theta1)\
    x2 = x1 + L2 * np.cos(theta1 + theta2)\
    y2 = y1 + L2 * np.sin(theta1 + theta2)\
    return (0, x1, x2), (0, y1, y2)

# Visualization setup
fig, ax = plt.subplots()\
plt.subplots_adjust(bottom=0.25)\
ax.set_xlim(-2, 2)\
ax.set_ylim(-2, 2)\
line, = ax.plot([], [], 'o-', lw=4)

# Sliders for joint angles
ax_theta1 = plt.axes([0.25, 0.1, 0.65, 0.03])\
ax_theta2 = plt.axes([0.25, 0.15, 0.65, 0.03])\
slider_theta1 = Slider(ax_theta1, 'Theta1', 0, 2*np.pi, valinit=0)\
slider_theta2 = Slider(ax_theta2, 'Theta2', 0, 2*np.pi, valinit=0)

# Update function
def update(val):\
    theta1 = slider_theta1.val\
    theta2 = slider_theta2.val\
    x_vals, y_vals = forward_kinematics(theta1, theta2)\
    line.set_data(x_vals, y_vals)\
    fig.canvas.draw_idle()

slider_theta1.on_changed(update)\
slider_theta2.on_changed(update)

# Initial draw
update(None)\
plt.title("2-Link Planar Arm Forward Kinematics")\
plt.grid(True)\
plt.show()


✅ Step 4: Validate with Test Cases\
θ₁ (deg)	θ₂ (deg)	Expected End-Effector Position\
0°	0°	(L1 + L2, 0)\
90°	0°	(0, L1 + L2)\
90°	90°	(-L2, L1)\
Use np.deg2rad() to convert degrees to radians for testing.
