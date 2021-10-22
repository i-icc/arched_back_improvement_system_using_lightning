#include <M5Core2.h>
#include <AXP192.h>

AXP192 power;

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

int n = 1;
int p = 0;

// the setup routine runs once when M5Stack starts up
void setup(){
  // Initialize the M5Stack object
  M5.begin();
  
  M5.IMU.Init();

  M5.Lcd.fillScreen(WHITE);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(2);
}

// the loop routine runs over and over again forever
void loop() {
    // put your main code here, to run repeatedly:
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
  M5.Lcd.setCursor(220, 42);
  M5.Lcd.print(" o/s");
  M5.Lcd.setCursor(0, 65);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
  M5.Lcd.setCursor(220, 87);
  M5.Lcd.print(" G");
  M5.Lcd.setCursor(0, 110);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);
  M5.Lcd.setCursor(220, 132);
  if (roll < 60){
    // 姿勢が悪いとバイブレーションで通知
    if (n != 1){
      p =1;
    }
    else{
      p = 0;
    }
    n = 1;
    // 振動ON
    power.SetLDOEnable(3, true);
  } else {
    n = 0;
    // 振動OFF
    power.SetLDOEnable(3, false);
  }
  M5.Lcd.print(" degree");
  M5.Lcd.setCursor(0, 177);
  M5.Lcd.printf("now : %d , p : %d", n,p);

  delay(1);
}
