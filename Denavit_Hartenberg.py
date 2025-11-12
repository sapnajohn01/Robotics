import numpy as np
import matplotlib.pyplot as plt

# Define DH parameters: [theta, d, a, alpha]
# For a planar 4-DOF arm, alpha and d are zero
def dh_transform(theta, d, a, alpha):
    ct, st = np.cos(theta), np.sin(theta)
    ca, sa = np.cos(alpha), np.sin(alpha)
    return np.array([
        [ct, -st*ca, st*sa, a*ct],
        [st, ct*ca, -ct*sa, a*st],
        [0, sa, ca, d],
        [0, 0, 0, 1]
    ])

# Link lengths
L = [1.0, 0.8, 0.6, 0.4]

# Joint angles (in radians)
theta = [np.deg2rad(45), np.deg2rad(-30), np.deg2rad(60), np.deg2rad(-15)]

# Compute transformation matrices
T = np.eye(4)
positions = [T[:2, 3]]  # Start at origin

for i in range(4):
    A = dh_transform(theta[i], 0, L[i], 0)
    T = T @ A
    positions.append(T[:2, 3])

# Plotting
x_vals, y_vals = zip(*positions)
plt.figure(figsize=(6, 6))
plt.plot(x_vals, y_vals, '-o', linewidth=2, markersize=8)
plt.xlim(-2, 2)
plt.ylim(-2, 2)
plt.grid(True)
plt.title("4-DOF Robotic Arm Visualization (DH Convention)")
plt.xlabel("X")
plt.ylabel("Y")
plt.gca().set_aspect('equal')
plt.show()
