#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 mpu(0x68);
int ax_offset(-736), ay_offset(-278), az_offset(1308);
int gx_offset(81), gy_offset(-28), gz_offset(65);
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();

  mpu.setXAccelOffset(ax_offset);
  mpu.setYAccelOffset(ay_offset);
  mpu.setZAccelOffset(az_offset);
  mpu.setXGyroOffset(gx_offset);
  mpu.setYGyroOffset(gy_offset);
  mpu.setZGyroOffset(gz_offset);

}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(" X: ");
  Serial.print(ax);
  Serial.print(" Y: ");
  Serial.print(ay);
  Serial.print(" Z: ");
  Serial.println(az);

  delay(1000);
}
