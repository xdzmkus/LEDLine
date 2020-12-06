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
	LedEffect::init();
	flashState = false;
}

bool FlashLedEffect::paint()
{
	if (!LedEffect::isReady())
		return false;

	if (flashState)
	{
		fillAllLeds(CRGB::Black);
	}
	else
	{
		fillAllLeds(flashColor);
	}

	flashState = !flashState;

	return true;
}
