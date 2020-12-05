/*
* LedEffect.cpp
*
*/

#include "LedEffect.h"

LedEffect::LedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: MillisTimer(Hz ? 1000UL / Hz : 0), ledLine(leds), numLeds(count)
{
	init();
}

LedEffect::~LedEffect()
{
}

void LedEffect::init()
{
	// zero out the led data managed by this effect
	memset8((void*)ledLine, 0, sizeof(struct CRGB) * numLeds);
}

CRGB LedEffect::getRandomColor() const
{
	return CRGB(CHSV(random(0, 255), 255, 255));
}

void LedEffect::fillAllLeds(CRGB color)
{
	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = color;
	}
}
