/*
By Ofer Haviv April-2015
This file contain an example how to send simple number to  7segment 4 bit (no fractions)
I made connection to 7seg 4 bit following the note in the folder

at the end to have the C value on the 7seg with one number after the point

using refresh with delay in millis
*/

#include <sevenSegmentLEDs.h>
// Define object name S to the sevenSegmentLEDs library
sevenSegmentLEDs S;

//for the delay
unsigned long previousMillis = 0; // last time update
long interval = 1000; // interval at which to do something (milliseconds

void setup() {
  
//begin command runs pinMode to all related pins
  S.begin();
}

void loop() {
  
  int num =1;
  int prevNum =1;
  unsigned long currentMillis;
  do 
  {
   currentMillis = millis();
    
    // send the number to the 7segment 
    S.sendNumber(num); 
    
      if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;  
    //do the math
    num += prevNum;
    prevNum = num - prevNum;
  }
  S.refresh();

  }while (num < 10000);

  


}
