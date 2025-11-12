**Assignment 4: Applying Denavit-Hartenberg Parameters to Model a Robot Arm**

🧠 **Step 1: Understand DH Convention**
The Denavit-Hartenberg (DH) convention standardizes how coordinate frames are assigned to each joint in a serial manipulator. For each link  , define four parameters:\
Parameter	Symbol	Description\
Link Length	 	Distance from  to  along\
Link Twist	 	Angle from  to  about\
Joint Offset	Distance from  to  along
Joint Angle	 Angle from  to  about

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
Each transformation from frame  to  is:\
Multiply these matrices in sequence:\
This gives the end-effector pose relative to the base.

✅ **Step 6: Validate with Forward Kinematics**\
Use geometric methods to compute the end-effector position:
 
Compare this with the position extracted from the final transformation matrix.\
🧪 Test Configurations

🧩 Python Script: DH-Based 2D Visualization\




