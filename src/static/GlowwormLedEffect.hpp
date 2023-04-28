/* 
* GlowwormLedEffect.hpp
*
*/

#ifndef __GLOWWORMLEDEFFECT_HPP__
#define __GLOWWORMLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numWorms>
class GlowwormLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static LedEffectName const name;

private:

	struct GWORM
	{
		CRGB rgb;
		uint16_t position;
		bool direction;
	}
	worms[numWorms];

	const CRGB wormColor;

public:

	GlowwormLedEffect(uint16_t Hz, CRGB color = CRGB::Black);
	~GlowwormLedEffect();

	void reset() override;
	void paint() override;

	operator LedEffectName () const { return name; }

private:

	GlowwormLedEffect(const GlowwormLedEffect&) = delete;
	GlowwormLedEffect& operator=(const GlowwormLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numWorms>
LedEffectName const GlowwormLedEffect<ledLine, numLeds, numWorms>::name = "GLOWWORM";

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numWorms>
GlowwormLedEffect<ledLine, numLeds, numWorms>::GlowwormLedEffect(uint16_t Hz, CRGB color)
	: ILedEffect(Hz), wormColor(color)
{
	reset();
}


template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numWorms>
GlowwormLedEffect<ledLine, numLeds, numWorms>::~GlowwormLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numWorms>
void GlowwormLedEffect<ledLine, numLeds, numWorms>::reset()
{
	ILedEffect::reset();

	uint8_t distance = numLeds / numWorms;

	for (uint8_t i = 0; i < numWorms; i++)
	{
		worms[i].rgb = wormColor ? wormColor : ILedLine<ledLine, numLeds>::getRandomColor();
		worms[i].position = i * distance;
		worms[i].direction = true;
	}

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds, const uint8_t numWorms>
void GlowwormLedEffect<ledLine, numLeds, numWorms>::paint()
{
	ILedLine<ledLine, numLeds>::clearAllLeds();

	for (uint8_t i = 0; i < numWorms; i++)
	{
		if (worms[i].direction)
		{
			worms[i].position++;
			if (worms[i].position == numLeds - 1)
			{
				worms[i].direction = false;
			}
		}
		else
		{
			worms[i].position--;
			if (worms[i].position == 0)
			{
				worms[i].direction = true;
			}
		}

		ledLine[worms[i].position] = worms[i].rgb;
	}
}

#endif
