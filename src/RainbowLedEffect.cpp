/* 
* RainbowLedEffect.cpp
*
*/


#include "RainbowLedEffect.h"


RainbowLedEffect::RainbowLedEffect(CRGB leds[], uint16_t count) : ILedEffect(leds, count), k(count != 0 ? 255/count : 1)
{
}

RainbowLedEffect::~RainbowLedEffect()
{
}

void RainbowLedEffect::refresh()
{
	hue += 5;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledStrip[i] = CHSV((uint8_t)(hue + i * k), 255, 255);
	}
}
