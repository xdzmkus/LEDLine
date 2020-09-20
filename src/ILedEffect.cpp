/*
* ILedEffect.cpp
*
*/

#include "ILedEffect.h"

ILedEffect::ILedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: ledLine(leds), numLeds(count)
{
	// zero out the led data managed by this effect
	memset8((void*)ledLine, 0, sizeof(struct CRGB) * numLeds);

	if (Hz != 0)
	{
		interval = 1000 / Hz;
		state = true;
	}
}

ILedEffect::~ILedEffect()
{
}

void ILedEffect::reset()
{
	// zero out the led data managed by this effect
	memset8((void*)ledLine, 0, sizeof(struct CRGB) * numLeds);

	timer = millis();
}

bool ILedEffect::paint()
{
	if (!state || (millis() - timer < interval))
		return false;

	timer = millis();
	return true;
}

uint32_t ILedEffect::getPixelColor(uint16_t pixel) const
{
	return (((uint32_t)ledLine[pixel].r << 16) | ((uint32_t)ledLine[pixel].g << 8) | (uint32_t)ledLine[pixel].b);
}

void ILedEffect::fillAllLeds(CRGB color) const
{
	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = color;
	}
}
