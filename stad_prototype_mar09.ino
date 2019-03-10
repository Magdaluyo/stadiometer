#include "LiquidCrystal.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

const int buzzer = 9; //buzzer to arduino pin 9
const int button = 12;
LiquidCrystal lcd(44,42,52,50,48,46); //Correlates to the RS,E,D4,D5,D6,D7
MPU6050 mpu(0x68);

int ax_offset(-736), ay_offset(-278), az_offset(1308);
int gx_offset(81), gy_offset(-28), gz_offset(65);
int16_t ax, ay, az;
int16_t gx, gy, gz;
int x_val;
int y_val;
int levelOffsetX = 1000;
int levelOffsetY = 1000;

int data[2800]; //vector to store readings
int valSize = 2800;

void setup() {
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(button, INPUT);

  tone(buzzer, 2500); // Send 2.5KHz sound signal...
  delay(75);        // 
  noTone(buzzer);     // Stop sound...
  delay(75);
  tone(buzzer, 2500); // Send 2.5KHz sound signal...
  delay(75);        // 
  noTone(buzzer);     // Stop sound...
  delay(75);
  tone(buzzer, 2500); // Send 2.5KHz sound signal...
  delay(75);        // 
  noTone(buzzer);     // Stop sound...

  Wire.begin();
  Serial.begin(9600);
  
  mpu.initialize();
  mpu.setXAccelOffset(ax_offset);
  mpu.setYAccelOffset(ay_offset);
  mpu.setZAccelOffset(az_offset);
  mpu.setXGyroOffset(gx_offset);
  mpu.setYGyroOffset(gy_offset);
  mpu.setZGyroOffset(gz_offset);
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  x_val = ax;
  y_val = ay;
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(A2, INPUT);
  
  Serial.begin(9600); 
  lcd.setCursor(5,0);
  lcd.print("Ready!");

}

void loop() {
  // put your main code here, to run repeatedly:

   int measurestate = 0;
   while(1) {
      measurestate = digitalRead(button);
      if(measurestate == HIGH) 
          break;
   }
   
   while(1) {
      mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      if(x_val < ax + levelOffsetX && x_val > ax - levelOffsetX && y_val < ax + levelOffsetY && y_val > ax - levelOffsetY)
          break;
      
      tone(buzzer, 3000 - ((abs(ax) + abs(ay))/50));
      delay(75); 
      noTone(buzzer);
      delay(250);
      
   }

   for(int i = 0; i < valSize; i++) {
      data[i] = analogRead(A2);
   }

   double avg = averagePos(data, valSize);
   refineValues(data, valSize, avg);
   avg = averagePos(data, valSize);
   double volt = (5000*avg)/1023;
//Using power function
   //double inches = 4164.85 * pow(avg,-.9765); // irsensor blue
   //double inches = 4300.85 * pow(avg,-.9765);
   //double cm = 10650.08 * pow(avg,-0.935) - 10;
   //double cm = inches * 2.54;

//Using inverse of distance to get linear equation
   
   double cm = (1/((volt - 1125)/137500)) - 1.5;    // height in cm
   double inches = cm/2.54;
   
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(inches);
   lcd.print(" in.");
   lcd.setCursor(0,1);
   lcd.print(cm);
   lcd.print(" cm");

   /*
   tone(buzzer, 2500); // Send 2.5KHz sound signal...
   delay(75);        // 
   noTone(buzzer);     // Stop sound...
   */

   delay(1000);

   //while(1) {}  // this is to pause the loop and keep one recorded number

}

double averagePos(int data[], int size) {
    int count = 0;
    double sum = 0;
    for(int i = 0; i < size; i++) {
        if(data[i] > 0) {
            sum += data[i];
            ++count;
        }
    }
    return sum/count;
}

void refineValues(int data[], int size, double average) {
    int diff = 1;
    for(int i = 0; i < size; i++) {
        if(data[i] > (average + diff) || data[i] < (average - diff)) {
            data[i] = -1;
        }
    }
}
