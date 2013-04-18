#include <Servo.h>

const int temperaturePin = 0;
const int piezoPin = 6;
const int servoPin = 7;
const int switchPin = 8;

const int interval = 3;
const int toneFrequency = 1000;
const int samples = 10;

const int closedAngle = 0;
const int openedAngle = 150;

int measurements = 0;
boolean closed = false;
Servo myServo;
long lastSwitchD = 0;

void setup() {
   Serial.begin(9600); 
   pinMode(piezoPin, OUTPUT);
   pinMode(switchPin, INPUT);
   myServo.attach(servoPin);
}

void loop() {
    
    if(digitalRead(switchPin) == HIGH && millis() - lastSwitchD > 50) {
      closed = !closed;
      lastSwitchD = millis();
    }
    
    if(closed) {
      myServo.write(closedAngle);
    }
    else {
      myServo.write(openedAngle);
    }
    if(millis() >= measurements*interval*1000) {
    
      //temperature measuring routine
      
      tone(piezoPin, toneFrequency);
      
      Serial.print("Temperature: ");
      Serial.print(measure());
      Serial.println(" degrees C");
      
      noTone(piezoPin);
      ++measurements;
    }
}

float measure() {
  
    float sum = 0;

    for(int i = 0; i < samples; i++) {
       sum = sum + analogRead(p) * 0.004882814;
       delay(20); 
    }
    return ((sum / (double)samples) - 0.5 ) * 100;
    
}

