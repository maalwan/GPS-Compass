# GPS-Compass
## Overview
A project that uses the ESP32, MPU6050, and NEO-6M GPS that guides users to stored locations while tracking distance and heading. It uses the [I2C Device Library](https://github.com/jrowberg/i2cdevlib) to communicate to the MPU6050 through I2C, the [TinyGPSPlus library](https://github.com/mikalhart/TinyGPSPlus) to decode the NMEA sentences from the NEO-6M, and the [U8G2 library](https://github.com/olikraus/u8g2) to display information on the OLED display. The ESP32 runs a control loop to communicate and regulate each of these devices individually and uses a button interrupt to get input from the user.
## Images
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/Protoboard%20Front.jpg" width="450" height="600" />
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/Protoboard%20Back.jpg" width="450" height="600" />
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/Components.jpg" width="450" height="600" />
<img src="https://github.com/maalwan/GPS-Compass/blob/main/photos/In%20case.jpg" width="450" height="600" />
