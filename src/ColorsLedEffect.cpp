/*
* ColorsLedEffect.cpp
*
*/

#include "ColorsLedEffect.h"

const char* const ColorsLedEffect::name = "COLORS";

ColorsLedEffect::ColorsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: LedEffect(leds, count, Hz)
{
	init();
}

ColorsLedEffect::~ColorsLedEffect()
{
}

void ColorsLedEffect::init()
{
	hue = 0;
	LedEffect::init();
}

bool ColorsLedEffect::paint()
{
	if (!isReady())
		return false;

	hue += 2;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV(hue, 255, 255);
	}

	return true;
}
