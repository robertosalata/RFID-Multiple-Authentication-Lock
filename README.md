# RFID Multiple Authentication Lock

## Overview

This Python script provides a two-factor authentication system using Authy OneTouch and RFID cards for the Encation project. The system authenticates users by reading their RFID card and sending a login request to their registered device using the Authy OneTouch API. The script runs on a Raspberry Pi with an RFID reader and uses the RPi.GPIO library to control the output pins.

## Copyright

Copyright (c) 2023 Roberto Salata. All rights reserved.

## Dependencies
- Python 3
- Authy API Python Client
- RPi.GPIO
- pyserial

To install the necessary dependencies, run the following:
```scss
pip install authy pyserial RPi.GPIO
```

## Usage
1. Create a text file named `user_ids.txt` containing user tags and their corresponding Authy user IDs, separated by a comma. Each user should be on a separate line. Example:
	```scss
	user_tag_1,12345
	user_tag_2,67890
	```
2. Update the `authy_api` variable with your Authy API key:
	```scss
	authy_api = AuthyApiClient('YOUR_AUTHY_API_KEY')
	```
3. Connect the RFID reader to the Raspberry Pi and update the `arduino` variable with the correct serial port:
	```Arduino
	arduino = serial.Serial('/dev/ttyACM0', 9600)
	```
4. Connect the output pins of the Raspberry Pi to the corresponding devices (e.g., door lock or alarm) and set up the GPIO pins in the script:
	```scss
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(17, GPIO.OUT)
	GPIO.setup(27, GPIO.OUT)
	```
5. Run the script on the Raspberry Pi:
	```scss
	python encation_auth.py
	```

The script will read RFID cards and check if they are registered in the `user_ids.txt` file. If the card is registered, it will send a OneTouch login request to the user's device. If the user approves the request within the time limit (default: 10 seconds), the script will activate the connected devices (e.g., unlock a door).

## License

This project is licensed under the terms of the MIT License. 
