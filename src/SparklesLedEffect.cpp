/* 
* SparklesLedEffect.cpp
*
*/

#include "SparklesLedEffect.h"

const char* const SparklesLedEffect::name = "SPARKLES";

SparklesLedEffect::SparklesLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color)
	: ILedLine(leds, count), ILedEffect(Hz), color(color)
{
	reset();
}

SparklesLedEffect::~SparklesLedEffect()
{
}

void SparklesLedEffect::reset()
{
	ILedEffect::reset();

	clearAllLeds();
}

bool SparklesLedEffect::paint()
{
	if (!isReady())
		return false;

	uint16_t thisNum = random(0, numLeds);

	if (!ledLine[thisNum])
	{
		ledLine[thisNum] = !color ? getRandomColor() : color;
	}

	for (uint16_t i = 0; i < numLeds; i++)
	{
		if (!ledLine[i]) continue;

		uint8_t maximum = max(max(ledLine[i].red, ledLine[i].green), ledLine[i].blue);

		float k = 0;

		if (maximum >= SPARKLES_TRACK_STEP)
		{
			k = (float)(maximum - SPARKLES_TRACK_STEP) / maximum;
		}

		ledLine[i] = CRGB(ledLine[i].red * k, ledLine[i].green * k, ledLine[i].blue * k);
	}

	return true;
}
