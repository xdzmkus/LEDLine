/*
* GlowwormLedEffect.cpp
*
*/


#include "GlowwormLedEffect.h"


GlowwormLedEffect::GlowwormLedEffect(CRGB leds[], uint16_t count, CRGB color) : ILedEffect(leds, count), rgb(color)
{
}


GlowwormLedEffect::~GlowwormLedEffect()
{
}

void GlowwormLedEffect::refresh()
{
	ledStrip[position] = CRGB::Black;

	if (direction)
	{
		position++;
		if (position == numLeds - 1)
		{
			direction = false;
		}
	}
	else
	{
		position--;
		if (position == 0)
		{
			direction = true;
		}
	}

	ledStrip[position] = rgb;
}
