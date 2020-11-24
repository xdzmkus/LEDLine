/*
* ColorsLedEffect.cpp
*
*/

#include "ColorsLedEffect.h"

const char* const ColorsLedEffect::name = "COLORS";

ColorsLedEffect::ColorsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: LedEffect(leds, count, Hz), hue(0)
{
}

ColorsLedEffect::~ColorsLedEffect()
{
}

void ColorsLedEffect::init()
{
	LedEffect::init();
	hue = 0;
}

bool ColorsLedEffect::paint()
{
	if (!LedEffect::isReady())
		return false;

	hue += 2;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV(hue, 255, 255);
	}

	return true;
}
