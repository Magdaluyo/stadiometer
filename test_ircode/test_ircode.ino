// Test code for the IR Sensor
double x, y;
double newVolt, newVolt1;
int data[1000]; //vector to store readings
int valSize = 1000;
//A0 is IR 1 and A1 is IR 2
void setup() 
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() 
{
   
   for(int i = 0; i < valSize; i++) {
      data[i] = analogRead(A0);
   }
   for(int i = 50; i < 100; i++) {
      //data[i] = analogRead(A1);
   }

   double avg = averagePos(data, valSize);
   refineValues(data, valSize, avg);
   avg = averagePos(data, valSize);

   //float inches = 4164.85 * pow(avg,-.9765);
    float inches = 4300 * pow(avg,-.9765); //irsensor red
   Serial.print("Inches: ");
   Serial.println(inches);

   while(1) {}
   /*
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
  */
}

double averagePos(int data[], int size) {
    int count = 0;
    double sum = 0;
    for(int i = 0; i < size; i++) {
        if(data[i] > 0) {
            sum += (int)data[i];
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
