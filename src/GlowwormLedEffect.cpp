/*
* GlowwormLedEffect.cpp
*
*/

#include "GlowwormLedEffect.h"

const char* const GlowwormLedEffect::name = "GLOWWORM";

GlowwormLedEffect::GlowwormLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: LedEffect(leds, count, Hz), rgb(color ? color : getRandomColor())
{
	init();
}


GlowwormLedEffect::~GlowwormLedEffect()
{
}

void GlowwormLedEffect::init()
{
	position = 0;
	direction = true;
	LedEffect::init();
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
