** 3kW LDC DC-DC Converter for EV/HEV Vehicles Software **


My software application:

This application software provides comprehensive software from BSW to ASW to control a DC/DC converter with
limited CPU usage. The low-level basic software configures the peripheral driver like PWM, ADC, Timer and CAN protocol. The application software provides the operation mode, control module, and diagnostic failure to help the converter operate safely. In addition, UDS services are also designed to upgrade the software via the CAN bus protocol.

What was Done:

- Create bar-metal software for the PWM module to operate the phase-shift full bridge topology

- Config a high-speed CAN protocol 500kbps to communicate with other ECU in a vehicle. ADC software was also added to provide ADC sensor value for the double-loop controller in application software. The other required software driver module like GPIO and timer is created.

- In the application parts, the doubled-loop controller is used to regulate the output voltage and current of the LDC converter.

- In diagnostic parts, LDC will detect the failure of over current, over/under voltage, and over temperature to protect the converter when it works in the abnormal condition. The fault signals are then sent to the vehicle control unit (VCU) via the CAN bus. 

- Another important feature is Unified Diagnostic Service which makes it possible to connect a computer (client) or diagnostics tool to the communication system of the vehicle. Thus, UDS requests can be sent to the controllers which must provide a response (this may be positive or negative). UDS service makes it possible to interrogate the fault memory of the individual control units and update a new firmware or to understand the environment and operating conditions of an ECU to be able to diagnose faulty or otherwise undesirable behaviour.
