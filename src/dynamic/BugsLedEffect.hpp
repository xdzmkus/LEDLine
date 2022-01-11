/* 
* BugsLedEffect.hpp
*
*/

#ifndef __BUGSLEDEFFECT_HPP__
#define __BUGSLEDEFFECT_HPP__

#include "internal/ILedLine.hpp"
#include "internal/ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
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
	*bugs = nullptr;

	const uint8_t numBugs;

public:

	BugsLedEffect(uint16_t Hz, uint8_t bugsCount = 0);
	~BugsLedEffect();
	
	void reset() override;
	void paint() override;

	operator const char* () const {	return name; }

	const uint8_t getNumBugs() const { return numBugs; };

private:

	BugsLedEffect(const BugsLedEffect&) = delete;
	BugsLedEffect& operator=(const BugsLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const BugsLedEffect<ledLine, numLeds>::name = "BUGS";

template <CRGB* const ledLine, const uint16_t numLeds>
BugsLedEffect<ledLine, numLeds>::BugsLedEffect(uint16_t Hz, uint8_t bugsCount)
	: ILedEffect(Hz), numBugs((bugsCount == 0 || bugsCount >= numLeds) ? random(1, constrain(numLeds, 1, 255)) : bugsCount)
{
	bugs = new BUGS[numBugs];
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
BugsLedEffect<ledLine, numLeds>::~BugsLedEffect()
{
	if (bugs != nullptr)
	{
		delete[] bugs;
		bugs = nullptr;
	}
}

template <CRGB* const ledLine, const uint16_t numLeds>
void BugsLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	if (bugs != nullptr)
	{
		for (uint8_t i = 0; i < numBugs; i++)
		{
			bugs[i].color = ILedLine<ledLine, numLeds>::getRandomColor();
			bugs[i].position = random(0, numLeds);
			bugs[i].speed += random(-5, 6);
		}
	}

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void BugsLedEffect<ledLine, numLeds>::paint()
{
	if (bugs == nullptr) return;

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
