#!/usr/bin/python

# works for python 2.7.9 (standard python on pi)
# compared with output from sensor files with printf's (no longer inside the files)

from sense_hat import SenseHat

sense = SenseHat()

print("Temperature from humidity: ", sense.get_temperature_from_humidity())
print("Temperature from pressure: ", sense.get_temperature_from_humidity())
print("Humidity: ", sense.get_humidity())
print("Pressure: ", sense.get_pressure())