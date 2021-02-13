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

	void fillAllLeds(CRGB color);
	void clearAllLeds();

	static CRGB getRandomColor();

private:

	ILedLine(const ILedLine&) = delete;
	ILedLine& operator=(const ILedLine&) = delete;

};

#endif
