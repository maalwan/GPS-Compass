// Button connection details
#define btnPin 33

// Variables changed in interrupt used to signal presses or change in button
volatile int btnMode = 0;
volatile long lastPress;
volatile boolean btnIsPressed = false;

// Interrupt on button, detects a short press vs long press
void IRAM_ATTR btnChange(void) {
  if (digitalRead(btnPin) == LOW) {
    lastPress = millis();
    btnIsPressed = true;
  } else if (btnIsPressed){
    long timeDiff = millis() - lastPress;
    if (timeDiff > 500) {
      btnMode = 2;
    } else if (timeDiff > 5) {
      btnMode = 1;
    }
    btnIsPressed = false;
  }
}

// Call at startup to initilize button interrupt
void btnSetup(void) {
  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(btnPin, btnChange, CHANGE);
  lastPress = millis();
}

// Returns last saved button press
int btnLoop(void) {
  int temp = btnMode;
  btnMode = 0;
  return temp;
}