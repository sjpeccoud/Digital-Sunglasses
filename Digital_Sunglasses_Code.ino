// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int arrayAverage = 0;           // the average



//Servo Setup
#include <Servo.h>
int servoPin = 9;
Servo servo;  
int angle = 0;   // servo position in degrees 

 //Photocell Startup No.1
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider        


 //Photocell Startup No.2
int photocellPin2 = 2;     // the cell and 10K pulldown are connected to a1
int photocellReading2;     // the analog reading from the sensor divider  

// Defines the average of the two photo cells
int photocellAverage;     

// The value that triggers the servo
int trigger = 900;


void setup(void) {
  
  //sends information via the Serial monitor
  Serial.begin(9600);   

  servo.attach(servoPin); 

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
 
void loop(void) {
  
  // Gets the reading of the two photocells from their analog ports
  photocellReading = analogRead(photocellPin);  
  photocellReading2 = analogRead(photocellPin2);

  // Finds the average of the two photocells for accuracy
  photocellAverage = (photocellReading + photocellReading2)/2;  

  // Prints the Average to the Serial Monitor
  Serial.print("Analog reading = ");
 // Serial.println(photocellAverage);
 
 
  
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(photocellAverage);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  arrayAverage = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(arrayAverage);
  
  
  if (arrayAverage > trigger)
  {
    
    servo.write(66);
  }
  else 
  {
    
    servo.write(190);
  }
 
  delay(50);  //delay inbetween reads for stability
}



