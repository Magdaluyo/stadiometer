// Test code for the IR Sensor
double x, y;
double newVolt, newVolt1;
double data[10]; //vector to store readings
//A0 is IR 1 and A1 is IR 2
void setup() 
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() 
{ 
   x = analogRead(A0);
   newVolt = x * (5.0 / 1023.0);
   Serial.println(newVolt);
   float inches = 3730 * pow(x,-0.935) - 3.937; // Calculates distance in inches
   float cm = 9730 * pow(x,-0.935) - 10; // Calculates distance in centimeters
    
  delay(100);
  Serial.print("Inches: "); // These few lines print to the serial monitor
  Serial.println(inches);
  Serial.print("Centimeters: ");
  Serial.println(cm);

  y = analogRead(A1);
  newVolt1 = y * (5.0/1023.0);
  Serial.println(newVolt1);
   float inches1 = 3730 * pow(y,-0.935) - 3.937; // Calculates distance in inches
   float cm1 = 9730 * pow(y,-0.935) - 10; // Calculates distance in centimeters
    
  delay(100);
  Serial.print("Inches: "); // These few lines print to the serial monitor
  Serial.println(inches1);
  Serial.print("Centimeters: ");
  Serial.println(cm1);
  Serial.println(" ");
  
  delay(2000);
}

/*for (int i = 0; i < 10; i++)
  {
    x = analogRead(A0);
    newVolt = x * (5.0 / 1023.0);
    Serial.println(newVolt);
    float inches = 3730 * pow(x,-0.935) - 3.937; // Calculates distance in inches
    float cm = 9730 * pow(x,-0.935) - 10; // Calculates distance in centimeters
    data(i) = inches;
    delay(100);
  }
  data(i) = inches;
  float distance = (data(0)+data(1)+data(2)+data(3)+data(4)+data(5)+data(6)+data(7)+data(8)+data(9))/10; //NEEDS ATTENTION*/
