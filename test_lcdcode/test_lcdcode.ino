#include "LiquidCrystal.h"

LiquidCrystal lcd(44,42,52,50,48,46);
int count = 0, i;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  
  
  
}

void loop() {
  lcd.setCursor(0,0);
  // put your main code here, to run repeatedly:
  for(i = 0; i < count;i++) {
    lcd.print(' ');
  }
  lcd.print("    Dominic");
  lcd.setCursor(0,1);
  lcd.print("   Magdaluyo");
  //count++;
  count = count % 17;
  delay(300);
}
