# RFID Multiple Authentication Lock
## Overview
This repository contains code for an access control system using RFID and two-factor authentication. The system reads RFID tags and authenticates users through Authy's OneTouch API. It also controls two red and yellow LEDs to indicate whether access is granted or denied. The code is developed for Arduino and Raspberry Pi platforms.

## Files
- `final.py`: Python code for the Raspberry Pi to handle RFID tag reading, user authentication, and LED control.
- `EncationArduinoCode.ino`: Arduino code for controlling the RFID reader and the two LEDs.
- `reader.ino`: Modified Arduino code that uses an SD card to store and read the list of accepted user RFID tags.
## Dependencies
- Python 3.x
- Authy API Python client: `pip install authy`
- RPi.GPIO: `pip install RPi.GPIO`
- PySerial: `pip install pyserial`
- Arduino libraries: SPI, MFRC522, and SD
## Usage
1. Make sure you have all the necessary dependencies installed.
	```scss
	pip install authy RPi.GPIO pyserial
	```
2. Clone the repository:
	```scss
	git clone https://github.com/robertosalata/RFID-Multiple-Authentication-Lock.git
	```
3. Add your Authy API key to `final.py`.
4. Update the list of accepted user RFID tags in `user_ids.txt` or in the Arduino sketch, depending on the version you choose to use.
5. Upload the `EncationArduinoCode.ino` or `reader.ino` (if using SD card) Arduino sketch to your Arduino board.
	- Open the Arduino IDE.
	- Load the desired sketch file (.ino) from the repository.
	- Connect your Arduino board to your computer.
	- Select the correct board and port in the Arduino IDE.
	- Click the "Upload" button.
6. Run the Raspberry Pi code:
	```scss
	python3 final.py
	```
## Hardware
- Raspberry Pi (with GPIO)
- Arduino board (e.g., Arduino Uno)
- MFRC522 RFID reader
- LEDs (red and yellow)
- SD card and SD card module (optional, only for `reader.ino`)
## License

Copyright (c) 2023 Roberto Salata

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
