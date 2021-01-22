/*
* ILedEffect.cpp
*
*/

#include "ILedEffect.h"

ILedEffect::ILedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: MillisTimer(Hz ? MillisTimer::CLOCKS_IN_SEC / Hz : 0), ledLine(leds), numLeds(count), speed(Hz)
{
}

ILedEffect::~ILedEffect()
{
}

CRGB ILedEffect::getRandomColor() const
{
	return CHSV(random(0, 255), 255, 255);
}

void ILedEffect::fillAllLeds(CRGB color)
{
	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = color;
	}
}

void ILedEffect::clearAllLeds()
{
	// zero out the led data managed by this effect
	memset8((void*)ledLine, 0, sizeof(struct CRGB) * numLeds);
}
