#include <sevenSegmentLEDs.h>
sevenSegmentLEDs S;
void setup() {
  // put your setup code here, to run once:
  S.dotSupport(true,13);
  S.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(1);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 3.3;
 voltage /= 1024.0; 
 
 // print out the voltage
// Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 16 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
//Serial.print(temperatureC); Serial.println(" degrees C");
  S.sendNumber(temperatureC,1); 
}
