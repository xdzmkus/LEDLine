/*
* BugsLedEffect.cpp
*
*/

#include "BugsLedEffect.h"

const char* const BugsLedEffect::name = "BUGS";

BugsLedEffect::BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugsCount)
	: ILedLine(leds, count), ILedEffect(Hz), numBugs(bugsCount)
{
	if (numBugs > 0)
	{
		bugs = new BUGS[numBugs];
	}

	reset();
}

BugsLedEffect::~BugsLedEffect()
{
	if (bugs != nullptr)
	{
		delete[] bugs;
		bugs = nullptr;
	}
}

void BugsLedEffect::reset()
{
	ILedEffect::reset();

	if (bugs != nullptr)
	{
		for (uint8_t i = 0; i < numBugs; i++)
		{
			bugs[i].color = getRandomColor();
			bugs[i].position = random16(0, numLeds);
			bugs[i].speed += random(-5, 6);
		}
	}

	clearAllLeds();
}

void BugsLedEffect::paint()
{
	if (bugs == nullptr)
		return;
		
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
			newPosition = static_cast<int16_t>(numLeds) - 1;
		}
		if (newPosition > static_cast<int16_t>(numLeds) - 1)
		{
			newPosition = 0;
		}

		bugs[i].position = newPosition;
    
		ledLine[bugs[i].position] = bugs[i].color;
	}
}
