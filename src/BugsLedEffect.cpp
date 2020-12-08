/*
* BugsLedEffect.cpp
*
*/

#include "BugsLedEffect.h"

const char* const BugsLedEffect::name = "BUGS";

BugsLedEffect::BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugs)
	: LedEffect(leds, count, Hz)
{
	numBugs = (bugs == 0) ? random(count / 10 + 1, count / 5 + 1) : bugs;

	bugColors = new CRGB[numBugs];
	bugPosition = new uint16_t[numBugs];
	bugSpeed = new int8_t[numBugs];

	init();
}

BugsLedEffect::~BugsLedEffect()
{
	delete[] bugColors;
	delete[] bugPosition;
	delete[] bugSpeed;
}

void BugsLedEffect::init()
{
	LedEffect::init();

	for (uint8_t i = 0; i < numBugs; i++)
	{
		bugColors[i] = getRandomColor();
		bugPosition[i] = random(0, numLeds);
		bugSpeed[i] += random(-5, 6);
	}
}

bool BugsLedEffect::paint()
{
	if (!LedEffect::isReady())
		return false;
		
	for (uint8_t i = 0; i < numBugs; i++)
	{
		ledLine[bugPosition[i]] = CRGB::Black;

		bugSpeed[i] += random(-5, 6);
		if (abs(bugSpeed[i]) > BUGS_MAX_SPEED)
		{
			bugSpeed[i] = 0;
		}

		int16_t newPosition = bugPosition[i] + bugSpeed[i] / 10;
		
		if (newPosition < 0)
		{
			newPosition = numLeds - 1;
		}
		if (newPosition > numLeds - 1)
		{
			newPosition = 0;
		}

		bugPosition[i] = newPosition;
    
		ledLine[bugPosition[i]] = bugColors[i];
	}

	return true;
}
