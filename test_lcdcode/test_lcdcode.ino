#include "LiquidCrystal.h"

LiquidCrystal lcd(44,42,52,50,48,46);
int count = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  for(int i = 0; i < count;i++) {
    lcd.print(' ');
  }
  lcd.print("      ENGR");
  lcd.setCursor(0,1);
  lcd.print("      110!");
  //count++;
  count = count % 17;
  delay(300);
}
