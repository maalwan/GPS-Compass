# GPS-Compass
## Overview
A project that uses the ESP32, MPU6050, and NEO-6M GPS to guide users to stored locations while tracking distance and heading. It uses the [I2C Device Library](https://github.com/jrowberg/i2cdevlib) to communicate to the MPU6050 through I2C, the [TinyGPSPlus library](https://github.com/mikalhart/TinyGPSPlus) to decode the NMEA sentences from the NEO-6M, and the [U8G2 library](https://github.com/olikraus/u8g2) to display information on the OLED display. The ESP32 runs a control loop to communicate and regulate each of these devices individually and uses a button interrupt to get input from the user.
## ESP-32
The ESP-32 is a compact, low power, and yet very powerful microcontroller. It is used to recieve data from the sensors, send information to the OLED display, and compute the necessary information to guide the user to stored locations.
## NEO-6M
The NEO-6M is a high precision, low power consumption GPS module. It's used for getting the latitude, longitude, and the absolute heading of the user while they are walking. It uses the UART communication protocol and sends NMEA sentences which are then decoded to obtain the relevant information.
## MPU-6050
The MPU-6050 is an accurate, low cost 6-axis accelerometer and gyroscope which is used to gather small relative turns that the user may make while navigating using the device. It cannot provide an absolute heading like the NEO-6M but can be used to account for small movements between GPS heading updates. It uses the the I2C protocol and returns a quaternion (which is a fusion of the accelerometer and gyroscope data) via the DMP (onboard processor) on the MPU-6050. This reduces error and drift.
## OLED 0.91 In
OLEDs of this size provide higher resolution quality and can be used for displaying a large amount of text while staying compact. It uses the I2C protocol to recieve information to display.
## Pins
### MPU6050
21 -> SDA\
22 -> SCL
### NEO-6M
16 -> RX\
17 -> TX
### OLED
26 -> SCL\
27 -> SDA
### Button
GROUND -> Button -> 33

## Images
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/Protoboard%20Front.jpg" width="450" height="600" />
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/Protoboard%20Back.jpg" width="450" height="600" />
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/Components.jpg" width="450" height="600" />
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/In%20case.jpg" width="450" height="600" />
