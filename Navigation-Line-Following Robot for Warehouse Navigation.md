Assignment 1: Line-Following Robot for Warehouse Navigation

Hardware setup and sensor placement
•	Chassis: Differential drive with two DC motors and a caster.
•	Sensors: At least two downward-facing IR reflectance sensors (analog recommended), spaced symmetrically around the line’s expected center.
•	Mounting height: 8–12 mm above floor; angle perpendicular to floor for consistent readings.
•	Tape and floor contrast: Matte black electrical tape on a lighter, non-reflective floor. Avoid glossy surfaces if possible.
•	Shielding:
o	Light shields: Small shrouds around sensors to reduce ambient light.
o	Cable management: Twisted pairs for sensor wires to reduce noise.
•	Suggested spacing:
o	Two-sensor setup: 20–30 mm between left and right sensors.
o	Optional third sensor: Center sensor improves error estimation and curve handling.
Tip: If the floor is glossy, lightly scuff the tape area or use matte gaffer tape to reduce specular reflections.
Sensor calibration under varying lighting
Goals
•	Establish dynamic thresholds that separate “black line” from “floor” under different lighting.
•	Normalize readings to a 0–1 range for robust PID inputs.
Strategy
•	Two-point calibration: Capture min/max values for each sensor over floor and over line.
•	Adaptive normalization: Maintain running min/max with slow adaptation to lighting drift.
•	Noise handling: Apply a small moving average or low-pass filter to sensor readings.

Arduino-style calibration routine

Tip: Store calibrated min/max in EEPROM and reload on boot. Recalibrate only when the environment changes significantly.
Line detection and error computation
Two-sensor error
•	Normalized readings:  , where 1 ≈ black line, 0 ≈ floor.
•	Error definition:  .
o	 when centered; positive means line shifts right; negative means left.
Robustness tweaks
•	Center confidence:  . Low  may indicate the line is out of both sensors—trigger a slow search.
•	Deadband: Small deadband on error (e.g.,  ) to prevent micro-oscillation.
•	Saturation handling: If one sensor reads near 1 and the other near 0, treat as edge case—reduce speed and bias toward the line.
PID motion control and speed management
Control law
•	Base speed: Forward speed when centered.
•	Differential speed: PID output adjusts left/right speeds to steer.
 
•	Motor commands:
o	 
o	 
Anti-jerk measures
•	Derivative filter: Compute  on filtered error.
•	Integral anti-windup: Clamp integral term.
•	Slew rate limit: Limit change in  per cycle.
•	Speed scheduling: Reduce  as  grows (indicative of tighter curve).
Arduino-style PID + motor control

Practical tuning guide
•	Start with P-only: Increase  until oscillations begin, then back off by ~20%.
•	Add D: Increase  to damp oscillations and reduce overshoot on curves.
•	Add small I: Use  to correct steady-state bias from asymmetric motors.
•	Retune base speed:
o	Straights: higher  .
o	Curves: ensure speed scheduling reduces speed enough to hold a 15 cm radius without losing the line.
Test plan and tuning procedure
Phase 1: straight sections
•	Setup: 2–3 m straight tape.
•	Targets:
o	Consistent tracking: ≥90% no deviation.
o	Smooth motion: No visible jerks; motor command changes are gradual.
o	Timing baseline: Measure completion time to compute “optimal” reference.
Phase 2: gentle curves (large radius ≥ 40 cm)
•	Actions: Introduce a single smooth arc; verify speed scheduling reduces speed as error grows.
•	Tune: Increase  slightly if overshoot appears; adjust  for time efficiency.
Phase 3: mixed curves (minimum radius 15 cm)
•	Course: Combine S-curves, gentle turns, and one sharp turn (≈15–20 cm radius).
•	Checks: Robot should not lose the line at entry/exit of sharp curves; observe that speed reduction is proportional to |error|.
Phase 4: complete circuit
•	Course: Straights + gentle + sharp turns in a loop.
•	Assess:
o	Success rate: ≥90% laps without failure.
o	Smoothness: No jerky reversals; consistent steering.
o	Time: Within 20% of the best lap achievable with safe parameters.
Tip: Log raw readings and motor commands over serial. Plot to see error, PID output, and speed scale—this makes tuning fast and objective.
Reliability enhancements and evaluation checklist
•	Enhancements
o	Center sensor (optional): Improve error estimate by using three sensors; compute weighted position estimate for better curve handling.
o	Lost-line recovery: If both sensors read floor for >200 ms, stop, gently pivot toward last known direction at reduced speed until the line is reacquired.
o	Ambient light guard: Add short skirts around sensors and run a brief auto-recalibration if average brightness shifts by >15%.
o	Motor symmetry: Calibrate per-motor PWM-to-speed mapping; apply a bias term so straight travel is truly straight.
•	Evaluation checklist
o	Consistent tracking:
	Metric: ≥90% lap success on the test circuit.
	Evidence: Logged error never saturates for >300 ms.
o	Smooth motion:
	Metric: PID output slew ≤ uSlew; minimal derivative spikes.
	Evidence: No rapid reversals or audible motor stutter.
o	Curve handling (≥15 cm radius):
	Metric: Robot maintains line without stopping; error bounded.
	Evidence: Speed scheduling engages; no tape exit.
o	Calibration robustness:
	Metric: Works under bright and dim lighting after two-point calibration.
	Evidence: Normalized readings keep 0–1 separation with low overlap.
o	Time efficiency:
	Metric: Lap time within 20% of the measured optimal with safe params.
	Evidence: Compare to baseline straight-line speed and best tuned lap.





