/*
* FlashLedEffect.cpp
*
*/

#include "FlashLedEffect.h"

FlashLedEffect::FlashLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: ILedEffect(leds, count, Hz), flashColor(color)
{
}

FlashLedEffect::~FlashLedEffect()
{
}

void FlashLedEffect::reset()
{
	ILedEffect::reset();
	flashState = false;
}

bool FlashLedEffect::paint()
{
	if (!ILedEffect::paint())
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
