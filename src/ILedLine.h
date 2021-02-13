/*
* ILedLine.h
*
*/

#ifndef _ILEDLINE_H
#define _ILEDLINE_H

#include <FastLED.h>

class ILedLine
{
protected:

	CRGB* const	ledLine;
	const uint16_t numLeds;

public:

	ILedLine(CRGB leds[], uint16_t count);
	virtual ~ILedLine();

	CRGB& operator[](uint16_t index);

protected:

	CRGB getRandomColor() const;
	void fillAllLeds(CRGB color);
	void clearAllLeds();
};

#endif
