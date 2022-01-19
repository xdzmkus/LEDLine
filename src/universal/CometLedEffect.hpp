/* 
* CometLedEffect.hpp
*
*/

#ifndef __COMETLEDEFFECT_HPP__
#define __COMETLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class CometLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static LedEffectName const name;

private:

	const uint8_t FADE_STEP = 10;

	const bool directionReversed;
	const uint16_t DELAY;
	const CRGB rgb;

	CRGB fade;
	uint16_t distance = 0;

public:

	CometLedEffect(uint16_t Hz, bool reversed = false, uint16_t distance = numLeds, CRGB color = CRGB::Black);
	~CometLedEffect();

	void reset() override;
	void paint() override;

	operator LedEffectName () const { return name; }

private:

	CometLedEffect(const CometLedEffect&) = delete;
	CometLedEffect& operator=(const CometLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
LedEffectName const CometLedEffect<ledLine, numLeds>::name = "COMET";

template <CRGB* const ledLine, const uint16_t numLeds>
CometLedEffect<ledLine, numLeds>::CometLedEffect(uint16_t Hz, bool reversed, uint16_t distance, CRGB color)
	: ILedEffect(Hz), directionReversed(reversed), DELAY(distance), rgb(color ? color : ILedLine<ledLine, numLeds>::getRandomColor())
{
	float k = FADE_STEP / 100.0;
	fade = CRGB(rgb.r * k, rgb.g * k, rgb.b * k);

	reset();
}


template <CRGB* const ledLine, const uint16_t numLeds>
CometLedEffect<ledLine, numLeds>::~CometLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void CometLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void CometLedEffect<ledLine, numLeds>::paint()
{
	if (!directionReversed)
	{
		// shift down all leds
		for (uint8_t y = 0; y < numLeds - 1; y++)
		{
			ledLine[y] = ledLine[y + 1];
		}

		// fill last led
		if (distance == 0)
		{
			ledLine[numLeds - 1] = rgb;
			distance = DELAY;
		}
		else if (ledLine[numLeds - 1])
		{
			ledLine[numLeds - 1] -= fade;
		}
	}
	else
	{
		// shift up all leds
		for (uint8_t y = numLeds - 1; y > 0; y--)
		{
			ledLine[y] = ledLine[y - 1];
		}

		// fill first led
		if (distance == 0)
		{
			ledLine[0] = rgb;
			distance = DELAY;
		}
		else if (ledLine[0])
		{
			ledLine[0] -= fade;
		}
	}

	--distance;
}

#endif
