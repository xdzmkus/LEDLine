/*
* FlashLedEffect.cpp
*
*/

#include "FlashLedEffect.h"

const char* const FlashLedEffect::name = "FLASH";

FlashLedEffect::FlashLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: LedEffect(leds, count, Hz), flashColor(color ? color : getRandomColor())
{
	init();
}

FlashLedEffect::~FlashLedEffect()
{
}

void FlashLedEffect::init()
{
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
