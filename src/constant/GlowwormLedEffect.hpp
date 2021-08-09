/* 
* GlowwormLedEffect.hpp
*
*/

#ifndef __GLOWWORMLEDEFFECT_HPP__
#define __GLOWWORMLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class GlowwormLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static const char* const name;

private:

	const CRGB rgb;
	uint16_t position = 0;
	bool direction = true;
	
public:

	GlowwormLedEffect(uint16_t Hz, CRGB color = CRGB::Black);
	~GlowwormLedEffect();

	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:

	GlowwormLedEffect(const GlowwormLedEffect&) = delete;
	GlowwormLedEffect& operator=(const GlowwormLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const GlowwormLedEffect<ledLine, numLeds>::name = "GLOWWORM";

template <CRGB* const ledLine, const uint16_t numLeds>
GlowwormLedEffect<ledLine, numLeds>::GlowwormLedEffect(uint16_t Hz, CRGB color)
	: ILedEffect(Hz), rgb(color ? color : ILedLine<ledLine, numLeds>::getRandomColor())
{
	reset();
}


template <CRGB* const ledLine, const uint16_t numLeds>
GlowwormLedEffect<ledLine, numLeds>::~GlowwormLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void GlowwormLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	position = 0;
	direction = true;

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void GlowwormLedEffect<ledLine, numLeds>::paint()
{
	ledLine[position] = CRGB::Black;

	if (direction)
	{
		position++;
		if (position == numLeds - 1)
		{
			direction = false;
		}
	}
	else
	{
		position--;
		if (position == 0)
		{
			direction = true;
		}
	}

	ledLine[position] = rgb;
}

#endif
