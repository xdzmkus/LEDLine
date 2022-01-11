/* 
* SparklesLedEffect.hpp
*
*/

#ifndef __SPARKLESLEDEFFECT_HPP__
#define __SPARKLESLEDEFFECT_HPP__

#include "internal/ILedLine.hpp"
#include "internal/ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class SparklesLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static const char* const name;

private:

	const uint8_t SPARKLES_TRACK_STEP = 20;

	const CRGB color;

public:

	SparklesLedEffect(uint16_t Hz, CRGB color = CRGB::Black);
	~SparklesLedEffect();

	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:

	SparklesLedEffect(const SparklesLedEffect&) = delete;
	SparklesLedEffect& operator=(const SparklesLedEffect&) = delete;
};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const SparklesLedEffect<ledLine, numLeds>::name = "SPARKLES";

template <CRGB* const ledLine, const uint16_t numLeds>
SparklesLedEffect<ledLine, numLeds>::SparklesLedEffect(uint16_t Hz, CRGB color)
	: ILedEffect(Hz), color(color)
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
SparklesLedEffect<ledLine, numLeds>::~SparklesLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void SparklesLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void SparklesLedEffect<ledLine, numLeds>::paint()
{
	uint16_t randLed = random(0, numLeds);

	if (!ledLine[randLed])
	{
		ledLine[randLed] = !color ? ILedLine<ledLine, numLeds>::getRandomColor() : color;
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
}

#endif
