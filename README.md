# Bladerunner Wi-Fi Control System

## Project Overview
This repository contains the implementation of a Wi-Fi-controlled Bladerunner system, developed as part of a university engineering project. The primary focus of the project was to design a control system that could manage the Bladerunner's carriage, including its operational status, speed, and door mechanisms, using wireless communication. 

The system enables real-time monitoring and control of the Bladerunner through a Wi-Fi network, ensuring efficient communication between the control software and the Bladerunner’s hardware.

## Features
- **Carriage Control**: Controls the speed and monitors the operational status of the Bladerunner in real-time.
- **Door Mechanism Control**: Sends and receives signals to open or close the Bladerunner's doors based on operational parameters.
- **Wi-Fi Communication**: Uses Wi-Fi to transmit data between the control unit and the Bladerunner, allowing remote access and monitoring.
- **Status Updates**: Provides continuous updates on the carriage's speed, operational status, and door states to ensure accurate performance tracking.

## System Architecture
The system is divided into several components:
1. **Carriage Control Program**: A Python-based program responsible for sending real-time instructions to the Bladerunner, including speed control and door mechanisms. It collects data from various sensors and relays critical status updates.
   
2. **Wi-Fi Communication Module**: This module handles the wireless data transmission between the control program and the Bladerunner, ensuring reliable and secure communication over the Wi-Fi network.

3. **Embedded System Interface**: This hardware interface connects the control program to the Bladerunner's mechanical components, such as the motors and door actuators.

## How It Works
The system operates through a continuous feedback loop:
- The control program monitors the status of the carriage and doors in real-time.
- Based on predefined parameters (e.g., speed limits, door status, operational mode), the control program sends commands to the Bladerunner via Wi-Fi.
- The Bladerunner responds by adjusting its operations (e.g., speed or door control), and feedback is sent back to the control program to confirm the execution.
- The system also handles error states, such as door malfunctions or speed control failures, and provides alerts for immediate troubleshooting.

## Technologies Used
- **Programming Language**: Python
- **Communication Protocol**: Wi-Fi (802.11)
- **Hardware Interface**: Embedded system for motor and door control
- **Control Logic**: Real-time control algorithms for speed and door management

## Installation and Setup
To set up and run the Bladerunner Wi-Fi control system:

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/bladerunner-wifi-control.git
   ```
2. Install the required Python dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Ensure your Wi-Fi module is properly configured and connected to the Bladerunner hardware.

4. Run the carriage control program:
   ```bash
   python carriage_control.py
   ```

## Usage
1. Launch the control program from your command line, specifying operational parameters like speed and door status.
2. Monitor real-time feedback to ensure the Bladerunner is operating as expected.
3. In case of any errors, review the system log for troubleshooting and diagnostics.