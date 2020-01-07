/*
* FlashLedEffect.cpp
*
*/


#include "FlashLedEffect.h"

FlashLedEffect::FlashLedEffect(CRGB leds[], uint16_t count, CRGB color, uint16_t delay, uint16_t times)
: ILedEffect(leds, count), flashColor(color), flashDelay(delay), flashCount(times)
{
	flashTime = millis();
}


FlashLedEffect::~FlashLedEffect()
{
}

void FlashLedEffect::refresh()
{
	if (flashCount != 0 && flashTime + flashDelay < millis())
	{
		if (flashState)
		{
			fillAllLeds(CRGB::Black);
		}
		else
		{
			if (flashCount > 0) flashCount--;
			fillAllLeds(flashColor);
		}
		flashState = !flashState;
		flashTime = millis();
	}
}
