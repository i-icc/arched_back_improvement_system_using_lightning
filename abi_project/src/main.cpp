#include <Arduino.h>
#include <M5Core2.h>

#define IMU_ADDRESS 0x68
#define IMU_COMMAND_ACCEL 0x3b
#define IMU_COMMAND_TEMP 0x41
#define IMU_COMMAND_GYRO 0x43

// プロトタイプ宣言
void readAccel(float *ax,float *ay,float *az);
void readGyro(float *gx,float *gy,float *gz);

void setup() {
  M5.begin(true,false,true,true);

  Serial.begin(115200);
  delay(1000);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);

  Wire.begin();
}

void loop() {
  float ax;
  float ay;
  float az;

  M5.Lcd.setCursor(220, 42);
  M5.Lcd.print("test");

  readAccel(&ax, &ay, &az);

  // Serial.printf("%e\n",ax);

  delay(100);
}

void readAccel(float *ax,float *ay,float *az){
  // 
  int8_t data[6] = {};
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(IMU_COMMAND_ACCEL);
  Wire.requestFrom(IMU_ADDRESS, 6);

  if (Wire.available() == 6){
    data[0] = Wire.read(); 
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }

  Serial.printf("%d,%d\n",data[0],data[1]);

  float aRes = 8.0/32768.9;

  *ax = float((data[0] << 8) + data[1]) * aRes;
  *ay = float((data[2] << 8) + data[3]) * aRes;
  *az = float((data[4] << 8) + data[5]) * aRes;
}