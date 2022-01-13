/* 
* FlashLedEffect.hpp
*
*/

#ifndef __FLASHLEDEFFECT_HPP__
#define __FLASHLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class FlashLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static LedEffectName const name;

private:

	const CRGB flashColor;
	bool flashState = false;
	
public:

	FlashLedEffect(uint16_t Hz, CRGB color = CRGB::Black);
	~FlashLedEffect();
	
	void reset() override;
	void paint() override;

	operator LedEffectName () const { return name; }

private:

	FlashLedEffect(const FlashLedEffect&) = delete;
	FlashLedEffect& operator=(const FlashLedEffect&) = delete;
};

template <CRGB* const ledLine, const uint16_t numLeds>
LedEffectName const FlashLedEffect<ledLine, numLeds>::name = "FLASH";

template <CRGB* const ledLine, const uint16_t numLeds>
FlashLedEffect<ledLine, numLeds>::FlashLedEffect(uint16_t Hz, CRGB color)
	: ILedEffect(Hz), flashColor(color ? color : ILedLine<ledLine, numLeds>::getRandomColor())
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
FlashLedEffect<ledLine, numLeds>::~FlashLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void FlashLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();
	flashState = false;
	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void FlashLedEffect<ledLine, numLeds>::paint()
{
	if (flashState)
	{
		ILedLine<ledLine, numLeds>::clearAllLeds();
	}
	else
	{
		ILedLine<ledLine, numLeds>::fillAllLeds(flashColor);
	}

	flashState = !flashState;
}

#endif
