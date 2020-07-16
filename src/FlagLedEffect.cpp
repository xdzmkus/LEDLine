/*
* FlagLedEffect.cpp
*
*/


#include "FlagLedEffect.h"


FlagLedEffect::FlagLedEffect(CRGB leds[], uint16_t count,
							 CRGB firstColor, uint16_t firstColorCount, 
							 CRGB secondColor, uint16_t secondColorCount, 
							 CRGB thirdColor, uint16_t thirdColorCount)
	: ILedEffect(leds, count), rgb1(firstColor), count1(firstColorCount), rgb2(secondColor), count2(secondColorCount), rgb3(thirdColor), count3(thirdColorCount)
{
}


FlagLedEffect::~FlagLedEffect()
{
}

void FlagLedEffect::refresh()
{
	uint16_t position = 0;
	
	if (count1 == 0 && count2 == 0 && count3 == 0) return;
	
	while (position < numLeds)
	{
		for (uint16_t firstColorCount = 0; firstColorCount < count1 && position < numLeds; firstColorCount++)
			ledLine[position++] = rgb1;
		for (uint16_t secondColorCount = 0; secondColorCount < count2 && position < numLeds; secondColorCount++)
			ledLine[position++] = rgb2;
		for (uint16_t thirdColorCount = 0; thirdColorCount < count3 && position < numLeds; thirdColorCount++)
			ledLine[position++] = rgb3;
	}
}
