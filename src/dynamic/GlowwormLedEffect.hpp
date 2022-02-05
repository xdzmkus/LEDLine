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

	static LedEffectName const name;

private:

	struct GWORM
	{
		CRGB rgb;
		uint16_t position;
		bool direction;
	}
	*worms = nullptr;

	const uint8_t numWorms;
	const CRGB wormColor;

public:

	GlowwormLedEffect(uint16_t Hz, uint8_t wormsCount = 0, CRGB color = CRGB::Black);
	~GlowwormLedEffect();

	void reset() override;
	void paint() override;

	operator LedEffectName () const { return name; };

	const uint8_t getNumWorms() const { return numWorms; };

private:

	GlowwormLedEffect(const GlowwormLedEffect&) = delete;
	GlowwormLedEffect& operator=(const GlowwormLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
LedEffectName const GlowwormLedEffect<ledLine, numLeds>::name = "GLOWWORM";

template <CRGB* const ledLine, const uint16_t numLeds>
GlowwormLedEffect<ledLine, numLeds>::GlowwormLedEffect(uint16_t Hz, uint8_t wormsCount, CRGB color)
	: ILedEffect(Hz), numWorms((wormsCount == 0 || wormsCount >= numLeds) ? random(1, constrain(numLeds, 1, 255)) : wormsCount), wormColor(color)
{
	worms = new GWORM[numWorms];
	reset();
}


template <CRGB* const ledLine, const uint16_t numLeds>
GlowwormLedEffect<ledLine, numLeds>::~GlowwormLedEffect()
{
	if (worms != nullptr)
	{
		delete[] worms;
		worms = nullptr;
	}
}

template <CRGB* const ledLine, const uint16_t numLeds>
void GlowwormLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	if (worms != nullptr)
	{
		uint8_t distance = numLeds / numWorms;

		for (uint8_t i = 0; i < numWorms; i++)
		{
			worms[i].rgb = (wormColor ? wormColor : ILedLine<ledLine, numLeds>::getRandomColor());
			worms[i].position = i * distance;
			worms[i].direction = true;
		}
	}

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void GlowwormLedEffect<ledLine, numLeds>::paint()
{
	if (worms == nullptr) return;

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
