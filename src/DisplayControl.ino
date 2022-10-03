#include <U8g2lib.h>

// OLED display connection
#define SDA 27
#define SCL 26

// Object used to control display (from U8G2 library)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE, SCL, SDA);

// Call at startup to initilize display 
void displaySetup() {
  display.begin();
  display.setFont(u8g2_font_profont11_tf);
  display.setFontPosTop();
}

// Various functions used to display text on display
void displayText(char* str1) {
  display.clearBuffer();
  display.drawStr(0, 0, str1);
  display.sendBuffer();
}
void displayText(char* str1, char* str2) {
  display.clearBuffer();
  display.drawStr(0, 0, str1);
  display.drawStr(0, 8, str2);
  display.sendBuffer();
}
void displayText(char* str1, char* str2, char* str3) {
  display.clearBuffer();
  display.drawStr(0, 0, str1);
  display.drawStr(0, 8, str2);
  display.drawStr(0, 16, str3);
  display.sendBuffer();
}
void displayText(char* str1, char* str2, char* str3, char* str4) {
  display.clearBuffer();
  display.drawStr(0, 0, str1);
  display.drawStr(0, 8, str2);
  display.drawStr(0, 16, str3);
  display.drawStr(0, 24, str4);
  display.sendBuffer();
}