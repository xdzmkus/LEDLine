/*
* ILedLine.cpp
*
*/

#include "ILedLine.h"

ILedLine::ILedLine(CRGB leds[], uint16_t count)
	: ledLine(leds), numLeds(count)
{
}

ILedLine::~ILedLine()
{
}

CRGB& ILedLine::operator[](uint16_t index)
{
	return ledLine[index];
}

void ILedLine::fillAllLeds(CRGB color)
{
	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = color;
	}
}

void ILedLine::clearAllLeds()
{
	// zero out the led data managed by this effect
	memset8((void*)ledLine, 0, sizeof(struct CRGB) * numLeds);
}

CRGB ILedLine::getRandomColor()
{
	return CHSV(random(0, 255), 255, 255);
}
