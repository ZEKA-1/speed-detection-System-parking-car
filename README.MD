# Smart Parking System with Car Speed Detection

## Project Overview

This project is an **Embedded System Smart Parking System** built using an **Arduino Mega 2560**.  
The system is designed to detect the speed of incoming cars and manage a parking gate automatically.

Before a car enters the parking area, the system measures its speed using two ultrasonic sensors. Based on the calculated speed, the system classifies the car movement as **LOW SPEED**, **NORMAL SPEED**, or **HIGH SPEED**. If the car is moving too fast, the buzzer gives an alert.

After the speed detection process, the parking system uses IR sensors to detect cars at the entrance and exit. A servo motor controls the gate, while an LCD screen displays the speed status, gate status, and the number of cars inside the garage.

---

## Main Features

- Car speed detection using two ultrasonic sensors
- Speed classification:
  - LOW SPEED
  - NORMAL SPEED
  - HIGH SPEED
- Automatic parking gate control using a servo motor
- Car entrance detection using IR sensor
- Car exit detection using IR sensor
- Parking capacity counter
- LCD display for real-time system information
- Buzzer alert when the car speed is high
- LED warning when the parking garage is full

---

## How the System Works

When a car approaches the parking entrance, it first passes in front of the first ultrasonic sensor. The Arduino records the time when the car is detected.

Then, the car passes in front of the second ultrasonic sensor. The Arduino records the second detection time.

The system calculates the speed using this formula:

```cpp
speed = distanceBetweenSensors / timeSec;