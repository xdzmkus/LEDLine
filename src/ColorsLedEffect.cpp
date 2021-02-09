/*
* ColorsLedEffect.cpp
*
*/

#include "ColorsLedEffect.h"

const char* const ColorsLedEffect::name = "COLORS";

ColorsLedEffect::ColorsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: ILedEffect(leds, count, Hz)
{
	reset();
}

ColorsLedEffect::~ColorsLedEffect()
{
}

void ColorsLedEffect::reset()
{
	ILedEffect::reset();

	hue = 0;

	clearAllLeds();
}

bool ColorsLedEffect::paint()
{
	if (!isReady())
		return false;

	hue += 2;

	fillAllLeds(CHSV(hue, 255, 255));

	return true;
}
