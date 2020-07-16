/*
* ColorsLedEffect.cpp
*
*/


#include "ColorsLedEffect.h"


ColorsLedEffect::ColorsLedEffect(CRGB leds[], uint16_t count)
	: ILedEffect(leds, count)
{
}

ColorsLedEffect::~ColorsLedEffect()
{
}

void ColorsLedEffect::refresh()
{
	hue += 2;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV(hue, 255, 255);
	}
}
