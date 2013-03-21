int tPin = 0;
int yLedPin = 2;
int rLedPin = 3;
int freq = 3000;

void setup() {
   Serial.begin(9600); 
   pinMode(yLedPin, OUTPUT);
   pinMode(rLedPin, OUTPUT);
}

void loop() {
  
    digitalWrite(yLedPin, HIGH);
    delay(freq);
    digitalWrite(yLedPin, LOW);
    digitalWrite(rLedPin, HIGH);
    Serial.print("Temperature: ");
    Serial.print(measure());
    Serial.println(" degrees C");
    digitalWrite(rLedPin,LOW);
}

float getVoltage(int p) {
    return ( analogRead(p) * 0.004882814);
}


float measure() {
  
    float sum = 0;
    
    for(int i = 0; i < 10; i++) {
       sum = sum + getVoltage(tPin);
       delay(20); 
    }
    return (sum / 10.0);
    
}

