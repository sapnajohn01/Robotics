<img width="566" height="21" alt="image" src="https://github.com/user-attachments/assets/0c89c389-127e-472c-a484-c27b19001f53" />**Assignment 4: Applying Denavit-Hartenberg Parameters to Model a Robot Arm**

🧠 **Step 1: Understand DH Convention**
The Denavit-Hartenberg (DH) convention standardizes how coordinate frames are assigned to each joint in a serial manipulator. For each link  , define four parameters:\
Parameter	Symbol	Description\
Link Length	a1 Distance from  to  along\
Link Twist	alpha1 	Angle from  to  about\
Joint Offset d1	Distance from  to  along
Joint Angle theta1 Angle from  to  about

🤖 **Step 2: Choose a Robotic Arm Configuration**\
Model a 4-DOF planar articulated arm with revolute joints. Assume:\
•	All joints rotate in the XY plane.\
•	Link lengths: L1=1.0,L2=0.8,L3=10.6,L4=0.4\
•	All joints are revolute.

📐 **Step 3: Assign Coordinate Frames**\
Follow these rules\
1.	 axis is along the axis of rotation.\
2.	 is perpendicular to both  and.\
3.	Origin is at the intersection of and.

📊 **Step 4: DH Parameter Table**\
Link
1	0	0	0
2	L1	0	0
3	L2	0	0
4	L3	0	0	

🔁 **Step 5: Transformation Matrices**\
Each transformation from frame i to i+1:\
Multiply these matrices in sequence:\
T(0-4)=T(0-1)+T(1-2)+T(2-3)+T(3-4)\
This gives the end-effector pose relative to the base.

✅ **Step 6: Validate with Forward Kinematics**\
Use geometric methods to compute the end-effector position:\
x=L1cos(theta1)+L2(cos(theta1+theta2))+L3(cos(theta1+theta2+theta3))+L4(cos(theta1+theta2+theta3+theta4))\
y=L1sin(theta1)+L2(sin(theta1+theta2))+L3(sin(theta1+theta2+theta3))+L4(sin(theta1+theta2+theta3+theta4))

Compare this with the position extracted from the final transformation matrix.\
🧪 Test Configurations

🧩 Python Script: DH-Based 2D Visualization\
[**Denavit_Hartenberg.py**](https://github.com/sapnajohn01/Robotics/blob/main/Denavit_Hartenberg.py)




