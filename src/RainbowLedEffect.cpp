/* 
* RainbowLedEffect.cpp
*
*/


#include "RainbowLedEffect.h"

const char* const RainbowLedEffect::name = "RAINBOW";

RainbowLedEffect::RainbowLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: LedEffect(leds, count, Hz), k(count != 0 ? 255/count : 1)
{
}

RainbowLedEffect::~RainbowLedEffect()
{
}

void RainbowLedEffect::init()
{
	LedEffect::init();
	hue = 0;
}

bool RainbowLedEffect::paint()
{
	if (!LedEffect::isReady())
		return false;

	hue += 5;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV((uint8_t)(hue + i * k), 255, 255);
	}

	return true;
}
