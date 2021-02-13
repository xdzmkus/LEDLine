/*
* ThreeColorLedEffect.cpp
*
*/

#include "ThreeColorLedEffect.h"

const char* const ThreeColorLedEffect::name = "THREECOLOR";

ThreeColorLedEffect::ThreeColorLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, THREECOLOR flag, uint8_t pulseTime, uint8_t pulseCount)
	: ILedLine(leds, count), ILedEffect(Hz), flag(flag), timesToFade(Hz* pulseTime), pulseCount(pulseCount)
{
	reset();
}

ThreeColorLedEffect::~ThreeColorLedEffect()
{
}

void ThreeColorLedEffect::reset()
{
	ILedEffect::reset();

	clearAllLeds();

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

bool ThreeColorLedEffect::paint()
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
		clearAllLeds();
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
