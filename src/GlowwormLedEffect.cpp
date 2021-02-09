/*
* GlowwormLedEffect.cpp
*
*/

#include "GlowwormLedEffect.h"

const char* const GlowwormLedEffect::name = "GLOWWORM";

GlowwormLedEffect::GlowwormLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: ILedEffect(leds, count, Hz), rgb(color ? color : getRandomColor())
{
	reset();
}


GlowwormLedEffect::~GlowwormLedEffect()
{
}

void GlowwormLedEffect::reset()
{
	ILedEffect::reset();

	position = 0;
	direction = true;

	clearAllLeds();
}

bool GlowwormLedEffect::paint()
{
	if (!isReady())
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
