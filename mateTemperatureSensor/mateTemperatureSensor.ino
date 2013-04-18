//Recount Inc. 
//Underwater Temperature Probe for MATE ROV
//Version 2.00 Beta

#include <Servo.h>
#include <SoftwareSerial.h>

const int temPin = 0;
const int TxPin = 6;

SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
float mean;
float sd;

long startMillis = 0;
int measurements = 0;

//editable section begins
const int interval = 2;  //time between measurements
const int samples = 250; //samples to take and average
const int sampleDelay = 1; //time between individual samples in ms
const float calibration = 0;
//editable section ends

void setup() {
  pinMode(TxPin,OUTPUT);
  digitalWrite(TxPin, HIGH);
  
  mySerial.begin(9600);
  delay(100);
  mySerial.write(12);
  mySerial.write(18);
  delay(5);
  mySerial.print("Recount Inc.");
  mySerial.write(13);
  mySerial.print("Thermometer 2.0");
  delay(2000);
  startMillis = millis();
}

void loop() {
  
  if(millis() - startMillis >= measurements*interval*1000) {
      measure();
      mySerial.write(12);
      mySerial.write(17);
      mySerial.print("t=");
      mySerial.print(measurements*interval);
      mySerial.print("s");
      mySerial.write(13);
      mySerial.print("T=");
      mySerial.print(mean);
      mySerial.print(" sd=");
      mySerial.print(sd);
      delay(500);
      mySerial.write(18);
    
    ++measurements;
  }
  
    //delay(interval * 1000 - 500 - samples*sampleDelay);
}

void measure() {

  float sum = 0;
  float data[samples];
  
  for(int i=0; i<samples; i++) {
     data[i] = getTemp();
     sum = sum +  data[i];
  }
  
  mean = sum / samples;
    
  float dSum = 0;
  
  for(int i=0; i<samples; i++) {
      dSum = dSum + pow(data[i] - mean, 2);
  }
  sd = sqrt(dSum / samples);
  
  
}

float getTemp() {
 return (analogRead(temPin) * 0.004882814 -0.5) * 100 + calibration;
}




