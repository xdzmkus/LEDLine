/* 
* BugsLedEffect.hpp
*
*/

#ifndef __BUGSLEDEFFECT_HPP__
#define __BUGSLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numBugs>
class BugsLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static const char* const name;

private:

	const uint8_t BUGS_MAX_SPEED = 20;

	struct BUGS
	{
		CRGB color;
		int8_t speed;
		uint16_t position;
	}
	bugs[numBugs];

public:

	BugsLedEffect(uint16_t Hz);
	~BugsLedEffect();
	
	void reset() override;
	void paint() override;

	operator const char* () const {	return name; }

private:

	BugsLedEffect(const BugsLedEffect&) = delete;
	BugsLedEffect& operator=(const BugsLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numBugs>
const char* const BugsLedEffect<ledLine, numLeds, numBugs>::name = "BUGS";

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numBugs>
BugsLedEffect<ledLine, numLeds, numBugs>::BugsLedEffect(uint16_t Hz)
	: ILedEffect(Hz)
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numBugs>
BugsLedEffect<ledLine, numLeds, numBugs>::~BugsLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numBugs>
void BugsLedEffect<ledLine, numLeds, numBugs>::reset()
{
	ILedEffect::reset();

	for (uint8_t i = 0; i < numBugs; i++)
	{
		bugs[i].color = ILedLine<ledLine, numLeds>::getRandomColor();
		bugs[i].position = random(0, numLeds);
		bugs[i].speed += random(-5, 6);
	}

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numBugs>
void BugsLedEffect<ledLine, numLeds, numBugs>::paint()
{
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

#endif
