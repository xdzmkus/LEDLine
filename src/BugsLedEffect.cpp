/*
* BugsLedEffect.cpp
*
*/

#include "BugsLedEffect.h"

const char* const BugsLedEffect::name = "BUGS";

BugsLedEffect::BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugsCount)
	: LedEffect(leds, count, Hz), numBugs((bugsCount == 0) ? random(count / 10 + 1, count / 5 + 1) : bugsCount)
{
	bugs = new BUGS[numBugs];

	init();
}

BugsLedEffect::~BugsLedEffect()
{
	delete[] bugs;
}

void BugsLedEffect::init()
{
	for (uint8_t i = 0; i < numBugs; i++)
	{
		bugs[i].color = getRandomColor();
		bugs[i].position = random(0, numLeds);
		bugs[i].speed += random(-5, 6);
	}

	LedEffect::init();
}

bool BugsLedEffect::paint()
{
	if (!isReady())
		return false;
		
	for (uint8_t i = 0; i < numBugs; i++)
	{
		ledLine[bugs[i].position] = CRGB::Black;

		bugs[i].speed += random(-5, 6);
		if (abs(bugs[i].speed) > BUGS_MAX_SPEED)
		{
			bugs[i].speed = 0;
		}

		int16_t newPosition = bugs[i].position + bugs[i].speed / 10;
		
		if (newPosition < 0)
		{
			newPosition = numLeds - 1;
		}
		if (newPosition > numLeds - 1)
		{
			newPosition = 0;
		}

		bugs[i].position = newPosition;
    
		ledLine[bugs[i].position] = bugs[i].color;
	}

	return true;
}
