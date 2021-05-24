import serial
import time
import keyboard
import io

arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)
while True:
    data = arduino.readline()
    if len(data) != 0:
        print(data)
        keyboard.write(data.decode("utf-8"))