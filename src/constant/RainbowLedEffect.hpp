/* 
* RainbowLedEffect.hpp
*
*/

#ifndef __RAINBOWLEDEFFECT_HPP__
#define __RAINBOWLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class RainbowLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static const char* const name;

private:

	const float k;
	uint8_t hue = 0;

public:

	RainbowLedEffect(uint16_t Hz);
	~RainbowLedEffect();
	
	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:

	RainbowLedEffect(const RainbowLedEffect&) = delete;
	RainbowLedEffect& operator=(const RainbowLedEffect&) = delete;
};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const RainbowLedEffect<ledLine, numLeds>::name = "RAINBOW";

template <CRGB* const ledLine, const uint16_t numLeds>
RainbowLedEffect<ledLine, numLeds>::RainbowLedEffect(uint16_t Hz)
	: ILedEffect(Hz), k(255 / numLeds + 1)
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
RainbowLedEffect<ledLine, numLeds>::~RainbowLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void RainbowLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	hue = 0;

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void RainbowLedEffect<ledLine, numLeds>::paint()
{
	hue += 5;

	for (uint16_t i = 0; i < numLeds; i++)
	{
		ledLine[i] = CHSV((uint8_t)(hue + i * k), 255, 255);
	}
}

#endif
