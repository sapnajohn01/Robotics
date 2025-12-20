Assignment 4: IoT Dashboard for Robot Telemetry Data Visualization

🔑 Key Telemetry Data\
Battery Voltage: Measured via voltage divider + ADC on ESP8266/ESP32.\
Motor Temperature: Use thermistors or digital temperature sensors (e.g., DS18B20) mounted near motors.\
Operation Time: Track uptime since last start/reset using internal timers.\
(Optional) Add metrics like current draw, error codes, or task completion status for richer insights.

⚙️ Robot-Side Implementation\
Data Logging:\
Write routines to read sensors periodically (e.g., every 15–30 seconds).\
Store readings in local variables or buffer for caching.\
Transmission to ThingSpeak:\
Use Wi-Fi (ESP8266/ESP32).\
Format data as HTTP GET/POST requests:

Code\
Implement retry logic:\
If transmission fails, cache data in local memory (e.g., array or SPIFFS).\
Retry when connectivity is restored.

📊 ThingSpeak Setup\
Channels:\
Create one channel per robot, or one channel with multiple fields (battery, temp, time).\
Note down Channel ID and Write API Key.

Dashboard:\
Use ThingSpeak’s widgets:\
Gauges for battery voltage.\
Line graphs for motor temperature trends.\
Numeric display for operation time.\
Enable historical tracking with time-series plots.\
Organize layout: one panel per robot, or grouped by metric across robots.

🛡️ Reliability & Error Handling\
Update Intervals:\
15–30 seconds is safe; ThingSpeak allows up to 1 update every 15 seconds per channel.

Error Handling:\
Detect failed HTTP requests.\
Cache unsent data locally.\
Implement exponential backoff for retries.

Data Recovery:\
On reconnect, flush cached data to ThingSpeak.\
Ensure timestamps are preserved for historical accuracy.

✅ Testing & Validation\
Simulate robot telemetry with dummy values first.\
Verify data appears correctly on ThingSpeak.\
Check update frequency doesn’t exceed platform limits.\
Validate dashboard readability: clear gauges, graphs, and historical plots.

🏆 Evaluation Criteria Alignment\
Accurate transmission → Sensor calibration + robust HTTP requests.\
Comprehensive dashboard → Gauges + graphs + historical plots.\
Appropriate intervals → 15–30s updates.

Error handling → Retry + caching.\
Professional layout → Organized per robot or per metric, intuitive visualization.
