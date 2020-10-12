/*
* BugsLedEffect.cpp
*
*/

#include "BugsLedEffect.h"

const char* const BugsLedEffect::name = "BUGS";

BugsLedEffect::BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugs)
	: LedEffect(leds, count, Hz)
{
	numBugs = (bugs == 0 || bugs >= count) ? random(count/10, count/5) : bugs;
	if (numBugs == 0) numBugs = 1;

	bugColors = new CRGB[numBugs];
	bugPosition = new uint16_t[numBugs];
	bugSpeed = new int8_t[numBugs];

	for (uint8_t i = 0; i < numBugs; i++)
	{
		bugColors[i] = CHSV(random(0, 9) * 28, 255, 255);
		bugPosition[i] = random(0, count);
		bugSpeed[i] += random(-5, 6);
	}
}

BugsLedEffect::~BugsLedEffect()
{
	delete[] bugColors;
	delete[] bugPosition;
	delete[] bugSpeed;
}

void BugsLedEffect::reset()
{
	LedEffect::reset();

	for (uint8_t i = 0; i < numBugs; i++)
	{
		bugColors[i] = CHSV(random(0, 9) * 28, 255, 255);
		bugPosition[i] = random(0, numLeds);
		bugSpeed[i] += random(-5, 6);
	}
}

bool BugsLedEffect::paint()
{
	if (!LedEffect::paint())
		return false;
		
	for (uint8_t i = 0; i < numBugs; i++)
	{
		ledLine[bugPosition[i]] = CRGB::Black;

		bugSpeed[i] += random(-5, 6);
		if (bugSpeed[i] == 0)
		{
			bugSpeed[i] = (-5, 6);
		}
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
