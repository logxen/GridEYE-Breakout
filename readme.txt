OVERVIEW

This is a breakout board for the Panasonic Grid-EYE AMG88xx line of thermopile arrays. The sensors are available in both 3.3v and 5v flavors and capture 8 by 8 pixels of far ir data.

The demo firmware is an Arduino sketch and runs on an arduino. (http://arduino.cc/) It probably requires at v1.0 ide. Check out Arduino docs for how to wire an i2c device.

The demo software is a Processing sketch. (http://processing.org/) Processing is what the Arduino ide is based on and I feel that they make a nice set. It expects to connect to the arduino via a serial port. You will need to manually set the serial port in the source file.

