/* 
* RainbowLedEffect.cpp
*
*/


#include "RainbowLedEffect.h"


RainbowLedEffect::RainbowLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: ILedEffect(leds, count, Hz), k(count != 0 ? 255/count : 1)
{
}

RainbowLedEffect::~RainbowLedEffect()
{
}

void RainbowLedEffect::reset()
{
	ILedEffect::reset();
	hue = 0;
}

bool RainbowLedEffect::paint()
{
	if (!ILedEffect::paint())
		return false;

	hue += 5;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV((uint8_t)(hue + i * k), 255, 255);
	}

	return true;
}
