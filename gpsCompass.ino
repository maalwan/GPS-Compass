#include <EEPROM.h>

// Heading updated in loop
double combinedHeading = 0;
// Pages used to display on OLED screen
#define pages 4
unsigned pos = 0;
void basicScreen(void);
void locationOne(void);
void locationTwo(void);
void locationThree(void);
typedef void screenPages(void);
screenPages* displayMode[pages] = {basicScreen, 
                        locationOne,
                        locationTwo, 
                        locationThree};

// Initial startup
void setup() {
  displaySetup();

  displayText("Accel/Gyro init", "Keep still");
  MPUSetup();  
  delay(500);

  displayText("GPS init", "May take a while");
  GPSSetup();
  delay(500);

  btnSetup();
  EEPROM.begin(pages * 2 * sizeof(double));
  displayText("Init complete");
  delay(500);
}

// Main control loop
void loop() {
  // Update information
  MPULoop();
  GPSLoop();
  updateHeading();
  configureCommand(btnLoop());

  // Display screen according the position the user has selected
  displayMode[pos]();
}

// Combines heading from GPS and Accelerometer
void updateHeading(void) {
  combinedHeading = getGPSDirection();
  if (combinedHeading != -1) {
    // If GPS is updated, zero the MPU to line up with GPS heading
    if (isGPSDirUpd()) { zeroMPU(); }
    // Between -180 and 180, apply to GPS direction and correct angle if necessary
    combinedHeading += getMPUHeading();
    if (combinedHeading > 360) { combinedHeading -= 360; }
    if (combinedHeading < 0) { combinedHeading += 360; }
  }
}

// Take command from button to change display or save information
void configureCommand(int command) {
  if (command == 1) {
    // Go to next page if a short press is detected
    ++pos;
    if (pos >= pages) { pos -= pages; }
  } else if (command == 2) {
    // Store location in EEPROM if long press is detected
    EEPROM.put(pos * 2 * sizeof(double), getLat()); 
    EEPROM.put(pos * 2 * sizeof(double) + sizeof(double), getLng());
    EEPROM.commit();
  }
}

// Saves location, distance and direction to strings in parameter to be displayed
void getDisplayLocation(char* locationStr, char* distanceStr, char* directionStr) {
  // Get lat and lng as a string
  double savedLat = -1, savedLng = -1;
  EEPROM.get(pos * 2 * sizeof(double), savedLat);
  EEPROM.get(pos * 2 * sizeof(double) + sizeof(double), savedLng);
  snprintf(locationStr, 30, "%.5f, %.5f", savedLat, savedLng);
  // Get distance as a string
  snprintf(distanceStr, 30, "Distance: %.3f miles", getDistance(savedLat, savedLng));
  // Get direction to show user where to go
  double headingToSavedLoc = getGPSCourseTo(savedLat, savedLng);
  if (abs(combinedHeading - headingToSavedLoc) < 10) {
    strcpy(directionStr, "^");
  } else if ((fmod(combinedHeading - headingToSavedLoc + 540, 360) - 180) < 0) {
    strcpy(directionStr, "->");
  } else {
    strcpy(directionStr, "<-");
  }
}

// Default screen for location pages
void locationScreen(char* title) {
  char locationStr[30];
  char distanceStr[30];
  char directionStr[30];
  getDisplayLocation(locationStr, distanceStr, directionStr);
  displayText(title, locationStr, distanceStr, directionStr);  
}

// Starting page, displays current location, heading, and distance from last saved location
void basicScreen(void) {
  // -1 if location or direction is invalid
  double lat = getLat();
  double lng = getLng();
  if (lat == -1 || lng == -1 || combinedHeading == -1) {
    displayText("GPS Disconnected!");
    return;
  }
  // Setup strings for display
  char latStr[30];
  char lngStr[30];
  char gpsDirStr[30];
  snprintf(latStr, 30, "Lat: %.5f", lat);
  snprintf(lngStr, 30, "Lng: %.5f", lng);
  snprintf(gpsDirStr, 30, "Direction: %.2f", combinedHeading);
  displayText(latStr, lngStr, gpsDirStr); 
}

// Three saved locations as different pages
void locationOne(void) {
  locationScreen("Location 1:");
}
void locationTwo(void) {
  locationScreen("Location 2:");
}
void locationThree(void) {
  locationScreen("Location 3:");
}