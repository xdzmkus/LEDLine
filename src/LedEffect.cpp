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

uint32_t LedEffect::getPixelColor(uint16_t pixel) const
{
	return (((uint32_t)ledLine[pixel].r << 16) | ((uint32_t)ledLine[pixel].g << 8) | (uint32_t)ledLine[pixel].b);
}

void LedEffect::fillAllLeds(CRGB color) const
{
	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = color;
	}
}
