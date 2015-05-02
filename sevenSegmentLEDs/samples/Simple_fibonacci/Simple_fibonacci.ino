/*
By Ofer Haviv April-2015
This file contain an example how to send simple number to  7segment 4 bit (no fractions)
I made connection to 7seg 4 bit following the note in the folder

at the end to have the C value on the 7seg with one number after the point
*/

#include <sevenSegmentLEDs.h>
// Define object name S to the sevenSegmentLEDs library
sevenSegmentLEDs S;
void setup() {
  
//begin command runs pinMode to all related pins
  S.begin();
}

void loop() {
  
  int num =1;
  int prevNum =1;
  
  do 
  {
 
    // send the number to the 7segment 
    S.sendNumber(num); 
    
    //do the math
    num += prevNum;
    prevNum = num - prevNum;
  }while (num < 10000);
  

}
