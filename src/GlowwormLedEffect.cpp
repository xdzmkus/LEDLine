/*
* GlowwormLedEffect.cpp
*
*/

#include "GlowwormLedEffect.h"

GlowwormLedEffect::GlowwormLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: ILedEffect(leds, count, Hz), rgb(color)
{
}


GlowwormLedEffect::~GlowwormLedEffect()
{
}

void GlowwormLedEffect::reset()
{
	ILedEffect::reset();
	position = 0;
	direction = true;
}

bool GlowwormLedEffect::paint()
{
	if (!ILedEffect::paint())
		return false;

	ledLine[position] = CRGB::Black;

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

	ledLine[position] = rgb;

	return true;
}
