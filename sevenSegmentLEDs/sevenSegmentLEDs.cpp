/* 
By Ofer Haviv April-2015

This library is for seven segment 4bit stack
for more information see my page on github https://github.com/oferhaviv/Arduino

Functions list: https://github.com/oferhaviv/Arduino/wiki/7segment%204bit%20functions

7segment 4bit functions list:
Must use function:
void begin(); begin is very common and actually doing pinMode OUPUT to all related pins

Most common functions:
void sendNumber(unsigned int num); The major function - send a number and it will show up on the 7seg 4bit
void sendNumber( float num, int numbersAfterDot); this function is pretty similar to the previous but you can use fractions and choose how many digits after the point to show. if choose to use it, you must init the point PIN with dotSupport function
void refresh(); this function can be use in the loop to keep the lights on if need

Optional functions:
void SegmentsPins (int segmentPins[]); i put some default wiring and its common one - you can choose different and change the segment pins
void DigitsPins (int digitPins[]); i put some default wiring and its common one - you can choose different and change the digits pins
void zeroWhenClear (bool zero); you can choose to have zero digits when empty - e.g. 48 will be present as 0048
void dotSupport (bool dotSupport, int dotPIN); must use this function when try to present fractions, define the point pin
*/
#include "sevenSegmentLEDs.h"

//private variables

int _totalSegments = 7;
const static int _numDigits = 4;   
int LEDdigitsPins[4] = {2, 3, 4, 5};
int sevenSegmentPins[8] = {6, 7, 8, 9, 10, 11, 12,13};
bool zeroLead = false;
int dig[7] = {0,0,0,0,0,0,0};
bool dotSupported= false;

// contractor FFU	
sevenSegmentLEDs::sevenSegmentLEDs()
{
	//contractor
}
// begin perform pinMode
void sevenSegmentLEDs::begin()
{
	//define all pins as OUTPUT
	for (int digitNum = 0 ; digitNum < _numDigits ; digitNum++) {
	pinMode(LEDdigitsPins[digitNum],OUTPUT); 
	}
	for (int segmentNum = 0 ; segmentNum < _totalSegments ; segmentNum++) {
	pinMode(sevenSegmentPins[segmentNum],OUTPUT);
	}	
	
	//if dot supported define it pin as output as well
	if (dotSupported)
	{
		pinMode(sevenSegmentPins[7],OUTPUT); 
	}
}

// optional for different pins set than the default
void sevenSegmentLEDs::SegmentsPins (int segmentPins[])
{
	//update all segment pins
	for (int segmentNum = 0 ; segmentNum < _totalSegments ; segmentNum++) {
		sevenSegmentPins[segmentNum] = segmentPins[segmentNum];
	}	
}

// optional for different pins set than the default
void sevenSegmentLEDs::DigitsPins (int digitPins[])
{
	//update all digits pin
	for (int digitNum = 0 ; digitNum < _numDigits ; digitNum++) {
		LEDdigitsPins[digitNum] = digitPins[digitNum];
	}	
}

// optional default is true - e.g. 12 will be shows as 0012 (always use all digits)
void sevenSegmentLEDs::zeroWhenClear (bool zero)
{
	//update zeroLead
	zeroLead = zero;
}

// optional - if dot supported what is the pin - using function sendNumber(float,int) will alwayes ture this to true
void sevenSegmentLEDs::dotSupport (bool dotSupport, int dotPIN)
{
	//update DOT support
	dotSupported= true;
	sevenSegmentPins[7] = dotPIN;
	
}


// Refresh the LEDs
void sevenSegmentLEDs::refresh()
{
	for (int digitNum = 0 ; digitNum < _numDigits ; digitNum++) {
	digitalWrite( LEDdigitsPins[digitNum], HIGH);    
  }	
}


// the easy way - send me number as it will put it on the LED stuck
void sevenSegmentLEDs::sendNumber(unsigned int num)
{
	dotSupported=false;
  //update dig1...4
  breakNumber(num);

  	//update all digits pin
  for (int digitNum = 0 ; digitNum < _numDigits ; digitNum++) {
	digitalWrite( LEDdigitsPins[digitNum], LOW);   
	drawNumber(dig[digitNum]);
	delay(DTime);
	digitalWrite( LEDdigitsPins[digitNum], HIGH);   
  }	

}
// overload: sendNumber(int) only with float with point
// shows the number with dot 4digits top you can select how many numbers after dot to show
// NOTE: don't use this if the is no dot support on your LED stack
void sevenSegmentLEDs::sendNumber( float num,int numbersAfterDot)
{
	dotSupported=true;
	if (numbersAfterDot >3){numbersAfterDot=3;}
	breakNumber(num);
	
	for (int digitNum = 0 ; digitNum < _numDigits ; digitNum++) {
	digitalWrite( LEDdigitsPins[digitNum], LOW);   
	if (digitNum ==3-numbersAfterDot)
	{
		drawNumber(dig[digitNum+numbersAfterDot],true);

	}else{
		drawNumber(dig[digitNum+numbersAfterDot]);
	}
	delay(DTime);
	digitalWrite( LEDdigitsPins[digitNum], HIGH);   
  }	
	
}

// internal method breaking the number to digits - in case of float support (AKA dot support) it take all 3 digits after the point
void sevenSegmentLEDs::breakNumber(float num)
{
  dig[0] = num / 1000;
  num = num - (dig[0] * 1000);
  dig[1] = num / 100;
  num = num - (dig[1] * 100);
  dig[2] = num / 10;
  num = num - (dig[2] *10);
  dig[3] = num;
num = num - dig[3];

  if (dotSupported)
  {
	  //take three numbers after the dot
	  dig[4] = num * 10;
	  num = (num * 10) - dig[4];
	  dig[5] = num * 10;
	  num = (num * 10) - dig[5];
	  dig[6] = num * 10;
	  num = (num * 10) - dig[6];
  }
  
  // remove leading zeros
  if (dig[0] == 0 )
  { 
    dig[0]=10;
    if (dig[1] == 0 )
    {
      dig[1]=10;
      {
        if (dig[2]==0)
        {
          dig[2]=10;
        }
      }
    }
  }
}



//internal: draw the number following the structure digits look like on the pins
void sevenSegmentLEDs::drawNumber(int n, bool dot)
{
	if (n > 9 && zeroLead)  {n=0;}
	for (int segmentNum = 0 ; segmentNum < _totalSegments ; segmentNum++) {
		bool _value = sevenSegmentValues[n][segmentNum];
		digitalWrite(sevenSegmentPins[segmentNum], _value);
	}
	
  	if (dotSupported)
	{
		digitalWrite(sevenSegmentPins[7], dot);
	}
}
//internal: overload of the drawNumber(int,bool) when the bool always false
void sevenSegmentLEDs::drawNumber(int n)
{
	drawNumber( n, false);
}
