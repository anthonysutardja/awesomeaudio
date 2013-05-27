#Awesome Audio Control
This is a project to create a physical distance-based gain controller for the audio output of a PC.

##Essential Files
###read.py
Reads the serial data from the USB port. You must find which serial port is the right one. Also, you must run read.py as root.

To investigate which serial port to read from:

    ls /dev/tty.*

Replace line 9 with this device. (e.g. `/dev/tty.usbmodemfa131`)

###Distance_LED.ino
Arduino stuff. Upload that to your arduino.

##Requirements
- Arduino Uno
- Distance sensor thing
- OSX
