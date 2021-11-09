#include <Arduino.h>
#include <M5Core2.h>

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.Lcd.print("test");
}