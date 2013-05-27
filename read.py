#!/usr/bin/env python
import serial
import subprocess
import math

MAX_DIST = 30.0

# Initialize Serial reader
ser = serial.Serial('/dev/tty.usbmodemfa131', 9600)


def volumeCommand(n):
    """
        n   :   integer from 0 to 10
        Returns a command string for commandline.
    """
    try:
        return """osascript -e \"set Volume """ + str(n) + """\" """
    except:
        return 0


def scale(f):
    """
        f   :   float distance reading in centimeters.
        Returns a number scaled integer accorsing to MAX_DIST.
    """
    return int(math.floor(f/MAX_DIST*10)) - 1

if __name__ == "__main__":
    #Loop for reading serial USB
    while 1:
        print ser.readline().strip().split(",")  # For debugging
        try:
            reading = float(ser.readline().strip().split(",")[1])
            level = scale(reading)
            if level >= 0 and level <= 10:
                command = volumeCommand(scale(reading))
                print command
                # Run system command
                subprocess.call(command, shell=True)
        except:
            pass
