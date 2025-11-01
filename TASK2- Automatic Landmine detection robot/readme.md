**🤖 Bluetooth Controlled Robot Car with Landmine Detector**

# 🚗 Overview

This project is a Bluetooth-controlled robotic vehicle powered by an Arduino UNO, L298N motor driver, HC-05 Bluetooth module, and servo-mounted metal detector.
It can move in multiple directions (forward, backward, left, right) using Bluetooth commands from a smartphone app and includes a servo motor for metal/ landmine detection sweep.

# ⚙️ Components Used

**Component     	Quantity	        Description**
Arduino UNO         	1	         Main microcontroller
L298N Motor Driver  	1	         Controls the DC motors
HC-05 Bluetooth Module	1	         Wireless communication with smartphone
Gear Motors (DC)	    4	         Drive wheels
Servo Motor         	1	         Moves metal detector back and forth
Metal Detector Module	1	         Detects metal objects
3.7V Li-ion Battery 	2	         Power supply for motors and circuit
Switch	                1	         Turns the system ON/OFF

Wires, Chassis, Wheels, etc.    	-	For mechanical assembly

# 🧠 Working Principle

    The car is controlled via Bluetooth commands from a smartphone app (like “Bluetooth Terminal” or “Bluetooth RC Controller”).

    The HC-05 module receives signals and sends them to the Arduino UNO.

    Based on received commands, the Arduino drives the motors using the L298N motor driver.

    The servo motor moves the metal detector sensor left and right for scanning.

    When metal/landmine is detected, the detector module sends a signal that can be used for alerts (e.g., LED or buzzer, optional).

# 📲 Bluetooth Commands
Command 	Action
F	        Move Forward
B	        Move Backward
L	        Rotate Left
R	        Rotate Right
S	        Stop
1	        Front Left
2	        Front Right
0	        Start Servo Sweep
5	        Stop Servo Sweep

# 🔌 Circuit Connections

1. Below is the simplified circuit layout for your reference:

2. Arduino UNO connected to L298N motor driver for motor control.

3. HC-05 Bluetooth Module connected to Arduino pins 2 (RX) and 3 (TX).

4. Servo Motor connected to pin 13.

5. L298N powered via 3.7V Li-ion batteries.

6. Metal Detector Module connected to Arduino for signal detection.

# 🧩 Arduino Pin Configuration

**Component**   	**Arduino Pin**
L298N ENA	             9
L298N IN1	             8
L298N IN2	             7
L298N ENB	             10
L298N IN3	             12
L298N IN4	             11
Servo Motor	             13
Bluetooth RX	         2
Bluetooth TX	         3

# 🧾 Code

1. The main Arduino sketch is provided in code.cpp
.
2. It handles:

        Bluetooth command reception

        Motor control logic

        Servo sweeping control

# ⚡ How to Run

1. Upload the code.cpp file to your Arduino UNO using the Arduino IDE.

2. Connect all components as per the circuit diagram.

3. Pair your smartphone with the HC-05 Bluetooth module (Default PIN: 1234 or 0000).

4. Open a Bluetooth terminal or robot controller app.

5. Send commands (F, B, L, R, S, etc.) to control the robot.

6. Use commands 0 and 5 to start and stop the servo-based metal detection sweep.

# 🪫 Power Supply

1. Use two 3.7V Li-ion batteries (in series) to provide around 7.4V to the L298N.

2. The Arduino UNO and HC-05 are powered via the 5V output of the motor driver.

# 🧱 Future Enhancements

 1. Add buzzer or LED indicator for metal detection alerts.

 2. Integrate obstacle avoidance sensors (like Ultrasonic).

 3. Add a camera module for remote monitoring.

 4. Use IoT (Wi-Fi) for long-distance control.

# 👨‍💻 Created by :

            Sumit Singh 
