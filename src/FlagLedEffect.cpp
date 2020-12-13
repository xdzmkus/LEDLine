/*
* FlagLedEffect.cpp
*
*/

#include "FlagLedEffect.h"

const char* const FlagLedEffect::name = "FLAG";

FlagLedEffect::FlagLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, FLAG flag, uint8_t pulseTime, uint8_t pulseCount)
	: LedEffect(leds, count, Hz), flag(flag), timesToFade(Hz* pulseTime), pulseCount(pulseCount)
{
	init();
}

FlagLedEffect::~FlagLedEffect()
{
}

void FlagLedEffect::init()
{
	LedEffect::init();

	uint16_t position = 0;

	while (position < numLeds)
	{
		for (uint16_t firstColorCount = 0;  position < numLeds && firstColorCount  < flag.count1; firstColorCount++)
			ledLine[position++] = flag.rgb1;
		for (uint16_t secondColorCount = 0; position < numLeds && secondColorCount < flag.count2; secondColorCount++)
			ledLine[position++] = flag.rgb2;
		for (uint16_t thirdColorCount = 0;  position < numLeds && thirdColorCount  < flag.count3; thirdColorCount++)
			ledLine[position++] = flag.rgb3;
	}

	if (timesToFade != 0)
	{
		fadeForRGB1 = CRGB(1 + flag.rgb1.r / timesToFade, 1 + flag.rgb1.g / timesToFade, 1 + flag.rgb1.b / timesToFade);
		fadeForRGB2 = CRGB(1 + flag.rgb2.r / timesToFade, 1 + flag.rgb2.g / timesToFade, 1 + flag.rgb2.b / timesToFade);
		fadeForRGB3 = CRGB(1 + flag.rgb3.r / timesToFade, 1 + flag.rgb3.g / timesToFade, 1 + flag.rgb3.b / timesToFade);
	}

	restOfFade = timesToFade;
	pulses = pulseCount;
}

bool FlagLedEffect::paint()
{
	if (!isReady() || timesToFade == 0)
		return false;

	// black(skipped) pulse?
	if (pulses == 0)
	{
		if (restOfFade == 0)
		{
			pulses = pulseCount;
			restOfFade = timesToFade;
		}
		else
		{
			restOfFade--;
		}
		return false;
	}

	// almost black (pulse done)?
	if (restOfFade == 0)
	{
		restOfFade = timesToFade;
		pulses--;
		fillAllLeds(CRGB::Black);
		return true;
	}

	uint16_t position = 0;

	while (position < numLeds)
	{
		if (restOfFade == timesToFade)
		{
			// show original flag
			for (uint16_t firstColorCount = 0;  position < numLeds && firstColorCount  < flag.count1; firstColorCount++)
				ledLine[position++] = flag.rgb1;
			for (uint16_t secondColorCount = 0; position < numLeds && secondColorCount < flag.count2; secondColorCount++)
				ledLine[position++] = flag.rgb2;
			for (uint16_t thirdColorCount = 0;  position < numLeds && thirdColorCount  < flag.count3; thirdColorCount++)
				ledLine[position++] = flag.rgb3;
		}
		else
		{
			// fade a bit
			for (uint16_t firstColorCount = 0;  position < numLeds && firstColorCount  < flag.count1; firstColorCount++)
				ledLine[position++] -= fadeForRGB1;
			for (uint16_t secondColorCount = 0; position < numLeds && secondColorCount < flag.count2; secondColorCount++)
				ledLine[position++] -= fadeForRGB2;
			for (uint16_t thirdColorCount = 0;  position < numLeds && thirdColorCount  < flag.count3; thirdColorCount++)
				ledLine[position++] -= fadeForRGB3;
		}
	}

	restOfFade--;

	return true;
}
