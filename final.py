from authy.api import AuthyApiClient
from datetime import datetime, timedelta
import serial
import time
import sys
import io
import os
import RPi.GPIO as GPIO

# Importing the necessary modules
from authy.api import AuthyApiClient
import time

# Function to load user IDs and tags from a text file
def load_user_ids(file_path):
    user_ids = {}
    if os.path.exists(file_path):
        with open(file_path, 'r') as f:
            for line in f:
                user_tag, user_id = line.strip().split(',')
                user_ids[user_tag] = int(user_id)
    return user_ids

# Initializing the AuthyApiClient object with the API key
authy_api = AuthyApiClient('jtJEfq9PPAdHOALNrt8FsVescO1C6RrZ')

# Load user IDs and tags from the text file
USER_IDS = load_user_ids('user_ids.txt')

# Time limit for waiting for the user to approve the login request
TIME_LIMIT = 10

# Function to authenticate the user with the given user tag
def authenticate_user(user_tag):
    # Get the Authy user ID for the given user tag
    user_id = USER_IDS.get(user_tag)
    if user_id is None:
        # If user tag is not found in the dictionary, print an error message and return
        print("Unknown user tag")
        return

    # Send a OneTouch request to the user's device with the given user ID and a message
    # asking for login approval. Set the expiration time to 120 seconds.
    response = authy_api.one_touch.send_request(
        user_id,
        "Requesting login for Encation",
        seconds_to_expire=120)

    # If the request is successful, print the UUID of the OneTouch request.
    # Otherwise, print the error message.
    if response.ok():
        print(response.get_uuid())
    else:
        print(response.errors())

    # Record the start time of waiting for the user's approval.
    start_time = time.time()
    approval_status = None

    # Loop until the user approves the request or the time limit is reached.
    while approval_status != "approved" and time.time() - start_time < TIME_LIMIT:
        # Wait for 1 second before checking the status again.
        time.sleep(1)

        # Get the approval status of the OneTouch request using the UUID.
        status = authy_api.one_touch.get_approval_status(response.get_uuid())
        approval_status = status.content["approval_request"]["status"]

    # If the user approves the request, print "yes". Otherwise, print "no".
    if approval_status == "approved":
        print('yes')
    else:
        print('no')

    return approval_status == "approved"


GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)

arduino = serial.Serial('/dev/ttyACM0', 9600)

data = []
while True:
    b = arduino.readline()
    string_n = b.decode()
    string = string_n.rstrip()
    s = str(string)

    if s.startswith("Card failed") or s.startswith("Error opening"):
        print(s)
        break

    if s and s not in data:
        print(s)
        data.append(s)

        if s in USER_IDS:
            is_approved = authenticate_user(s)
            if is_approved:
                GPIO.output(17, True)
                GPIO.output(27, True)
                time.sleep(5)
                GPIO.output(17, False)
                GPIO.output(27, False)

