Assignment 3: Wall-Following Robot for Corridor Navigation

🛠 Sensor Setup\
•	Mount ultrasonic or IR sensors on the side facing the wall (left or right depending on mode).\
•	Add a front-facing sensor to detect obstacles directly ahead (useful for corners).\
•	Optional: a second side sensor slightly angled forward to help anticipate corners.\
⚙️ Control Algorithm (Proportional Control)\
•	Define target distance:\
•	Measure current distance:\
•	Compute error:\
•	Apply proportional correction to steering:
 
Where  is the proportional gain tuned to minimize oscillation.\
•	This keeps the robot hugging the wall smoothly, correcting deviations without overreacting.\
🔄 Corner Handling\
•	Detection: Sudden large increase in side distance (e.g., >40 cm within a short time).\
•	Action: Use front sensor to confirm wall presence ahead. If wall disappears, execute a smooth turn toward the wall side.\
•	Implementation: Pre-programmed arc turn until side sensor reacquires wall at ~20 cm.\
🚪 Doorway Detection\
•	Pattern: Temporary increase in side distance (door opening), followed by return to normal wall distance.\
•	Logic: If side distance increases but front sensor still detects wall ahead, ignore the opening and continue straight.\
•	Avoid false turns: Only initiate corner maneuver if both side distance increases and front sensor shows no wall.\
↔️ Left & Right Wall Following\
•	Implement a mode switch: left-wall or right-wall following.\
•	Mirror the control logic depending on which side sensor is active.\
•	Useful for corridors where patrol direction changes.\
✅ Evaluation Criteria Alignment\
•	Consistent distance: Proportional control tuned to keep ±5 cm error.\
•	Smooth corners: Corner detection + arc turning prevents losing track.\
•	Doorway handling: Logic prevents unnecessary turns.\
•	Bidirectional: Mode switch supports left/right walls.\
•	Minimal oscillation: Careful tuning of  and possibly adding a small derivative term (PD control) reduces hunting.\
🚀 Testing Strategy\
1.	Start in a straight corridor, test distance maintenance.\
2.	Add corners (90° turns), verify smooth navigation.\
3.	Add doorways, confirm robot ignores them.\
4.	Switch between left and right wall following modes.\
5.	Adjust gains until oscillation is minimal.

