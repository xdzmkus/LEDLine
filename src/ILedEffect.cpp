/*
* ILedEffect.cpp
*
*/

#include "ILedEffect.h"

ILedEffect::ILedEffect(CRGB leds[], uint16_t count)
 : ledStrip(leds), numLeds(count)
{
	if(ledStrip)
	{
		// zero out the led data managed by this effect
		memset8((void*)ledStrip, 0, sizeof(struct CRGB) * numLeds);
	}
}

 ILedEffect::~ILedEffect()
{
}

uint32_t ILedEffect::getPixelColor(uint16_t pixel) const
{
	return (((uint32_t)ledStrip[pixel].r << 16) | ((uint32_t)ledStrip[pixel].g << 8) | (uint32_t)ledStrip[pixel].b);
}

void ILedEffect::fillAllLeds(CRGB color) const
{
	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledStrip[i] = color;
	}
}
