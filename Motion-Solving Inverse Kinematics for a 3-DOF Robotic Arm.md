Assignment 3: Solving Inverse Kinematics for a 3-DOF Robotic Arm

🧠 Step 1: Understanding Inverse Kinematics\
Inverse kinematics is the process of determining joint parameters (angles or displacements) that achieve a desired end-effector position. Unlike forward kinematics, IK can have:\
•	Multiple solutions (e.g., elbow-up vs elbow-down)\
•	No solution (if the target is outside the workspace)\
•	Singularities (where small changes in position cause large changes in joint angles)

🦾 Step 2: Arm Configuration Assumption\
We'll assume a planar RRR arm with:\
•	Link lengths:\
•	Joint angles:\  
•	Target position:  in 2D (extendable to 3D with orientation)

📐 Step 3: Deriving Inverse Kinematics Equations\
Forward Kinematics:\
math\
x = L_1 \cos(\theta_1) + L_2 \cos(\theta_1 + \theta_2) + L_3 \cos(\theta_1 + \theta_2 + \theta_3)\
y = L_1 \sin(\theta_1) + L_2 \sin(\theta_1 + \theta_2) + L_3 \sin(\theta_1 + \theta_2 + \theta_3)

Inverse Kinematics (Geometric Approach):\
1.	Compute wrist position:\
math\
x_w = x - L_3 \cos(\phi)\
y_w = y - L_3 \sin(\phi)\
where  is the desired orientation of the end-effector.\
Use Law of Cosines to find  :\
math\
D = \frac{x_w^2 + y_w^2 - L_1^2 - L_2^2}{2 L_1 L_2}\
\theta_2 = \arccos(D)\
•  Use Law of Sines or tangent method to find  :\
math\
\theta_1 = \arctan2(y_w, x_w) - \arctan2(L_2 \sin(\theta_2), L_1 + L_2 \cos(\theta_2))\
•  Compute  from orientation:\
math\
\theta_3 = \phi - \theta_1 - \theta_2

💻 Step 4: Python Implementation

import numpy as np\
def inverse_kinematics(x, y, phi, L1, L2, L3):\
    x_w = x - L3 * np.cos(phi)\
    y_w = y - L3 * np.sin(phi)\
    D = (x_w**2 + y_w**2 - L1**2 - L2**2) / (2 * L1 * L2)\
    if abs(D) > 1:\
        return None  # No solution\
    theta2_options = [np.arccos(D), -np.arccos(D)]\
    solutions = []

    for theta2 in theta2_options:\
        theta1 = np.arctan2(y_w, x_w) - np.arctan2(L2 * np.sin(theta2), L1 + L2 * np.cos(theta2))\
        theta3 = phi - theta1 - theta2\
        solutions.append((theta1, theta2, theta3))

    return solutions
    
🧭 Step 5: Handling Multiple Solutions\
You can select the best solution using:\
•	Minimal joint movement (compare with current joint angles)\
•	Avoiding joint limits\
•	Favoring elbow-down or elbow-up configurations\
Example:\
def select_best_solution(solutions, current_angles):\
    def cost(sol):\
        return sum(abs(sol[i] - current_angles[i]) for i in range(3))\
    return min(solutions, key=cost)
    
🧪 Step 6: Validation with Forward Kinematics\
python\
def forward_kinematics(theta1, theta2, theta3, L1, L2, L3):\
    x = L1 * np.cos(theta1) + L2 * np.cos(theta1 + theta2) + L3 * np.cos(theta1 + theta2 + theta3)\
    y = L1 * np.sin(theta1) + L2 * np.sin(theta1 + theta2) + L3 * np.sin(theta1 + theta2 + theta3)\
    return x, y
    
🧨 Step 7: Testing Edge Cases\
•	Targets near max reach:  \
•	Targets near origin\
•	Targets requiring full extension or folding
