#include "LiquidCrystal.h"

LiquidCrystal lcd(44,42,52,50,48,46);

int data[500]; //vector to store readings
int valSize = 500;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(A0, INPUT);
  Serial.begin(9600); 
  //lcd.setCursor(5,0);
  //lcd.print("Ready!");

}

void loop() {
  // put your main code here, to run repeatedly:

  //while(1) {}

   for(int i = 0; i < valSize; i++) {
      data[i] = analogRead(A0);
   }

   double avg = averagePos(data, valSize);
   //refineValues(data, valSize, avg);
   //avg = averagePos(data, valSize);

   double inches = 4164.85 * pow(avg,-.9765); // irsensor blue
   //float inches = 4300 * pow(avg,-.9765); // irsensor red
   lcd.setCursor(0,0);
   lcd.print(inches);
   lcd.print(" in.");
   

   while(1) {}

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
