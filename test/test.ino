#include <M5Stack.h>
#include <IMU_6886.h>

IMU_6886 imu6886;

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.Lcd.print("test");
}
