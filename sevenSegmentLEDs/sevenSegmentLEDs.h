/* 
By Ofer Haviv April-2015
Functions definition and constant of values for 7seg show numbers

*/

#ifndef sevenSegmentLEDs_h
#define sevenSegmentLEDs_h

#include "Arduino.h"

class sevenSegmentLEDs
{
public:
	sevenSegmentLEDs();
	void SegmentsPins (int segmentPins[]);
	void DigitsPins (int digitPins[]);
	void zeroWhenClear (bool zero);
	void dotSupport (bool dotSupport, int dotPIN);
	void sendNumber(unsigned int num);
	void sendNumber( float num, int numbersAfterDot);
	void begin();
	void refresh();
private:
 
	void drawNumber(int dig);
	void drawNumber(int dig, bool dot);
	void breakNumber(float num);
	const static int DTime = 4;
	const bool sevenSegmentValues[13][7] PROGMEM = {
		{1, 1, 1, 1, 1, 1, 0},  //zero
		{0, 1, 1, 0, 0, 0, 0},//one
		{1, 1, 0, 1, 1, 0, 1}, //two
		{1, 1, 1, 1, 0, 0, 1}, //three
		{0, 1, 1, 0, 0, 1, 1}, //four
		{1, 0, 1, 1, 0, 1, 1}, //five
		{1, 0, 1, 1, 1, 1, 1}, //six
		{1, 1, 1, 0, 0, 0, 0}, //seven
		{1, 1, 1, 1, 1, 1, 1}, //Eight
		{1, 1, 1, 1, 0, 1, 1},  //nine
		{0, 0, 0, 0, 0, 0, 0}, //clear
		{0, 0, 1, 1, 1, 0, 1}, //low circle
		{1, 1, 0, 0, 0, 1, 1} //high circle

	};

};
#endif