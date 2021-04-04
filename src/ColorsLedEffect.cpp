/*
* ColorsLedEffect.cpp
*
*/

#include "ColorsLedEffect.h"

const char* const ColorsLedEffect::name = "COLORS";

ColorsLedEffect::ColorsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: ILedLine(leds, count), ILedEffect(Hz)
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

void ColorsLedEffect::paint()
{
	hue += 2;

	fillAllLeds(CHSV(hue, 255, 255));
}
