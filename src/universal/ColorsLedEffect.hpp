/* 
* ColorsLedEffect.hpp
*
*/

#ifndef __COLORSLEDEFFECT_HPP__
#define __COLORSLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class ColorsLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static LedEffectName const name;

private:

	uint8_t hue;
	
public:

	ColorsLedEffect(uint16_t Hz);
	~ColorsLedEffect();

	void reset() override;
	void paint() override;

	operator LedEffectName () const { return name; }

private:

	ColorsLedEffect(const ColorsLedEffect&) = delete;
	ColorsLedEffect& operator=(const ColorsLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
LedEffectName const ColorsLedEffect<ledLine, numLeds>::name = "COLORS";

template <CRGB* const ledLine, const uint16_t numLeds>
ColorsLedEffect<ledLine, numLeds>::ColorsLedEffect(uint16_t Hz)
	: ILedEffect(Hz)
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
ColorsLedEffect<ledLine, numLeds>::~ColorsLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void ColorsLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	hue = 0;

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void ColorsLedEffect<ledLine, numLeds>::paint()
{
	hue += 2;

	ILedLine<ledLine, numLeds>::fillAllLeds(CHSV(hue, 255, 255));
}

#endif
