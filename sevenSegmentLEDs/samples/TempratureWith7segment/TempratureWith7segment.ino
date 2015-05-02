/*
By Ofer Haviv April-2015
This file contain an example how to use the 7segment 4 bit with fractions
I made connection to 7seg 4 bit following the note in the folder
here the sensor is connected to analog pin #1

at the end to have the C value on the 7seg with one number after the point
*/

#include <sevenSegmentLEDs.h>
// Define object name S to the sevenSegmentLEDs library
sevenSegmentLEDs S;
void setup() {

// because fraction i define another pin (#13) for the dot symbol on the 7seg
// note: this must be before begin() otherwise the dot pin is note getting pinMode
  S.dotSupport(true,13);
  
//begin command runs pinMode to all related pins
  S.begin();
}

void loop() {
  
  //analog read and calculate number must be float (so it can be fraction)
  //this code might be change depend on your temperature sensor or any other
  int reading = analogRead(1);  
  float voltage = reading * 3.3;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 16 ; 
  
  // send the number to the 7segment 
  // the number 1 present how many numbers after the dot
  S.sendNumber(temperatureC,1); 
}
