#include "FlagLedEffect.h"

FlagLedEffect::FlagLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, FLAG flag, uint8_t fadeInSec)
	: ILedEffect(leds, count, Hz), flag(flag), timesToFade(Hz*fadeInSec)
{
	if (timesToFade != 0)
	{
		fadeForRGB1 = max(max(flag.rgb1.r, flag.rgb1.g), flag.rgb1.b) / timesToFade + 1;
		fadeForRGB2 = max(max(flag.rgb2.r, flag.rgb2.g), flag.rgb2.b) / timesToFade + 1;
		fadeForRGB3 = max(max(flag.rgb3.r, flag.rgb3.g), flag.rgb3.b) / timesToFade + 1;
	}

	restOfFade = timesToFade;
}

FlagLedEffect::~FlagLedEffect()
{
}

void FlagLedEffect::reset()
{
	ILedEffect::reset();

	uint16_t position = 0;

	for (uint16_t firstColorCount = 0; firstColorCount < flag.count1 && position < numLeds; firstColorCount++)
		ledLine[position++] = flag.rgb1;
	for (uint16_t secondColorCount = 0; secondColorCount < flag.count2 && position < numLeds; secondColorCount++)
		ledLine[position++] = flag.rgb2;
	for (uint16_t thirdColorCount = 0; thirdColorCount < flag.count3 && position < numLeds; thirdColorCount++)
		ledLine[position++] = flag.rgb3;

	restOfFade = timesToFade;
}

bool FlagLedEffect::paint()
{
	if (!ILedEffect::paint() || timesToFade == 0)
		return false;

	if (restOfFade > timesToFade)
	{
		restOfFade--;
		return false;
	}

	if (restOfFade == 0)
	{
		restOfFade = timesToFade<<1;
		fillAllLeds(CRGB::Black);
		return true;
	}

	uint16_t position = 0;

	if (restOfFade == timesToFade)
	{
		for (uint16_t firstColorCount = 0; firstColorCount < flag.count1 && position < numLeds; firstColorCount++)
			ledLine[position++] = flag.rgb1;
		for (uint16_t secondColorCount = 0; secondColorCount < flag.count2 && position < numLeds; secondColorCount++)
			ledLine[position++] = flag.rgb2;
		for (uint16_t thirdColorCount = 0; thirdColorCount < flag.count3 && position < numLeds; thirdColorCount++)
			ledLine[position++] = flag.rgb3;
	}
	else
	{
		for (uint16_t firstColorCount = 0; firstColorCount < flag.count1 && position < numLeds; firstColorCount++)
			ledLine[position++].subtractFromRGB(fadeForRGB1);
		for (uint16_t secondColorCount = 0; secondColorCount < flag.count2 && position < numLeds; secondColorCount++)
			ledLine[position++].subtractFromRGB(fadeForRGB2);
		for (uint16_t thirdColorCount = 0; thirdColorCount < flag.count3 && position < numLeds; thirdColorCount++)
			ledLine[position++].subtractFromRGB(fadeForRGB3);
	}

	restOfFade--;

	return true;
}
