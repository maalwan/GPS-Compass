#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include <Wire.h>

// UART connection
#define RXD2 16
#define TXD2 17
#define GPSBaud 9600
HardwareSerial uart(1);

// Object and variable used for GPS
TinyGPSPlus gps;
boolean GPSUpdStatus = false;

// Direction calcuated from GPS location changes, -1 if invalid
double getGPSDirection(void){
  if (gps.course.isValid()) {
    return gps.course.deg();
  }
  return -1;
}

// Only returns true if GPS is updated from the last time checked
boolean isGPSDirUpd(void) {
  if (GPSUpdStatus) {
    GPSUpdStatus = false;
    return true;
  }
  return false;
}

// Direction from current location to location in parameter, -1 if current location is invalid
double getGPSCourseTo(double lat, double lng) {
  if (gps.location.isValid()) {
      return TinyGPSPlus::courseTo(
        gps.location.lat(),
        gps.location.lng(),
        lat, 
        lng);
  }
  return -1;
}

// Get distance in miles from current location to location in parameter, -1 if current location is invalid
double getDistance(double lat, double lng) {
  if (gps.location.isValid()) {
    // Returns distance in meters so must be converted to miles
    return TinyGPSPlus::distanceBetween(
        gps.location.lat(),
        gps.location.lng(),
        lat, 
        lng) * 0.000621371;
  }
  return -1;
}

// Get location, -1 if location is invalid
double getLat(void) {
  if (gps.location.isValid()) {
    return gps.location.lat();
  }
  return -1;
}
double getLng(void) {
  if (gps.location.isValid()) {
    return gps.location.lng();
  }
  return -1;
}

// Call at startup, delay until GPS connects to satellite
void GPSSetup(void) {
  uart.begin(GPSBaud, SERIAL_8N1, RXD2, TXD2);
  while (!gps.location.isValid()) {
    GPSLoop();
    delay(10);
  }
}

// Reads data from UART connection to GPS module
void GPSLoop(void) {
  while (uart.available()) {
    gps.encode(uart.read());
    // For some reason, course will report updated even if it is not if the GPS is not moving
    // so checking if the course equals exactly zero is required
    if (gps.course.isUpdated() && gps.course.deg() != 0) { 
      GPSUpdStatus = true; 
      }
  }
}