/* 
* SparklesLedEffect.cpp
*
*/

#include "SparklesLedEffect.h"

const char* const SparklesLedEffect::name = "SPARKLES";

SparklesLedEffect::SparklesLedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: LedEffect(leds, count, Hz)
{
}

SparklesLedEffect::~SparklesLedEffect()
{
}

bool SparklesLedEffect::paint()
{
	if (!LedEffect::isReady())
		return false;

	uint16_t thisNum = random(0, numLeds);

	if (getPixelColor(thisNum) == 0)
	{
		ledLine[thisNum] = getRandomColor();
	}

	for (uint16_t i = 0; i < numLeds; i++)
	{
		uint32_t thisColor = getPixelColor(i);

		if (thisColor == 0) continue;

		uint8_t rgb[3];
		rgb[0] = (thisColor >> 16) & 0xff;
		rgb[1] = (thisColor >> 8) & 0xff;
		rgb[2] = thisColor & 0xff;

		uint8_t maximum = max(max(rgb[0], rgb[1]), rgb[2]);

		float k = 0;

		if (maximum >= SPARKLES_TRACK_STEP)
		{
			k = (float)(maximum - SPARKLES_TRACK_STEP) / maximum;
		}

		ledLine[i] = CRGB(rgb[0] * k, rgb[1] * k, rgb[2] * k);
	}

	return true;
}
