/* 
* RainbowLedEffect.cpp
*
*/


#include "RainbowLedEffect.h"

const char* const RainbowLedEffect::name = "RAINBOW";

RainbowLedEffect::RainbowLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: LedEffect(leds, count, Hz), k(255/count + 1)
{
	init();
}

RainbowLedEffect::~RainbowLedEffect()
{
}

void RainbowLedEffect::init()
{
	hue = 0;
	LedEffect::init();
}

bool RainbowLedEffect::paint()
{
	if (!isReady())
		return false;

	hue += 5;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV((uint8_t)(hue + i * k), 255, 255);
	}

	return true;
}
