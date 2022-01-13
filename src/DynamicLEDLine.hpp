/*
* DynamicLEDLine.hpp
*
*/

#ifndef _DYNAMICLEDLINE_HPP_
#define _DYNAMICLEDLINE_HPP_

#include "LEDLine.h"
#include "DynamicLEDLineEffects.h"
#include "UniversalLEDLineEffects.h"

template <CRGB* const leds, const uint16_t numLeds>
class DynamicLEDLine : public LEDLine
{
private:

	static const uint8_t NUM_EFFECTS = 9;
	static LedEffectName const availableEffects[NUM_EFFECTS];

public:

	DynamicLEDLine() 
	{
	};

	virtual ~DynamicLEDLine()
	{
	};

	virtual uint8_t howManyEffects() const override
	{
		return NUM_EFFECTS;
	};

	virtual LedEffectName const* getAllEffectsNames() const override
	{
		return availableEffects;
	};

	virtual bool setEffectByName(LedEffectName effectName) override
	{
		if (strcmp(BouncingBallsLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new BouncingBallsLedEffect<leds, numLeds>(50);
		}
		else if (strcmp(BugsLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new BugsLedEffect<leds, numLeds>(20);
		}
		else if (strcmp(ColorsLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new ColorsLedEffect<leds, numLeds>(10);
		}
		else if (strcmp(FlameLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new FlameLedEffect<leds, numLeds>(10);
		}
		else if (strcmp(FlashLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new FlashLedEffect<leds, numLeds>(1);
		}
		else if (strcmp(GlowwormLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new GlowwormLedEffect<leds, numLeds>(30);
		}
		else if (strcmp(RainbowLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new RainbowLedEffect<leds, numLeds>(10);
		}
		else if (strcmp(SparklesLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new SparklesLedEffect<leds, numLeds>(20);
		}
		else if (strcmp(ThreeColorLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete activeEffect; activeEffect = new ThreeColorLedEffect<leds, numLeds>(30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 });
		}
		else
		{
			return false;
		}

		if (activeEffect != nullptr) activeEffect->start();

		return true;
	};
};


template <CRGB* const leds, const uint16_t numLeds>
LedEffectName const DynamicLEDLine<leds, numLeds>::availableEffects[NUM_EFFECTS] =
{
	BouncingBallsLedEffect<leds, numLeds>::name,
	BugsLedEffect<leds, numLeds>::name,
	ColorsLedEffect<leds, numLeds>::name,
	FlameLedEffect<leds, numLeds>::name,
	FlashLedEffect<leds, numLeds>::name,
	GlowwormLedEffect<leds, numLeds>::name,
	RainbowLedEffect<leds, numLeds>::name,
	SparklesLedEffect<leds, numLeds>::name,
	ThreeColorLedEffect<leds, numLeds>::name
};

#endif
