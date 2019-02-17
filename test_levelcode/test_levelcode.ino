#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 mpu(0x68);

int gx_offset(90), gy_offset(-24), gz_offset(32);
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();
  
  mpu.setXGyroOffset(gx_offset);
  mpu.setYGyroOffset(gy_offset);
  mpu.setZGyroOffset(gz_offset);

}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(" X: ");
  Serial.print(gx);
  Serial.print(" Y: ");
  Serial.print(gy);
  Serial.print(" Z: ");
  Serial.println(gz);

  delay(1000);
}
