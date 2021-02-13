/*
* FlashLedEffect.cpp
*
*/

#include "FlashLedEffect.h"

const char* const FlashLedEffect::name = "FLASH";

FlashLedEffect::FlashLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: ILedLine(leds, count), ILedEffect(Hz), flashColor(color ? color : getRandomColor())
{
	reset();
}

FlashLedEffect::~FlashLedEffect()
{
}

void FlashLedEffect::reset()
{
	ILedEffect::reset();
	flashState = false;
	clearAllLeds();
}

bool FlashLedEffect::paint()
{
	if (!isReady())
		return false;

	if (flashState)
	{
		clearAllLeds();
	}
	else
	{
		fillAllLeds(flashColor);
	}

	flashState = !flashState;

	return true;
}
