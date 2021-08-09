/*
* DynamicLEDLine.hpp
*
*/

#ifndef _DYNAMICLEDLINE_HPP_
#define _DYNAMICLEDLINE_HPP_

#include "LEDLine.h"
#include "DynamicLEDLineEffects.h"

template <CRGB* const leds, const uint16_t numLeds>
class DynamicLEDLine : public LEDLine
{
private:

	static const uint8_t NUM_EFFECTS;
	static const char* const availableEffects[];

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

	virtual const char* const* getAllEffectsNames() const override
	{
		return availableEffects;
	};

	virtual bool setEffectByName(const char* effectName) override
	{
		if (strcmp(BouncingBallsLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new BouncingBallsLedEffect<leds, numLeds>(50);
		}
		else if (strcmp(BugsLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new BugsLedEffect<leds, numLeds>(20);
		}
		else if (strcmp(ColorsLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new ColorsLedEffect<leds, numLeds>(10);
		}
		else if (strcmp(FlameLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new FlameLedEffect<leds, numLeds>(10);
		}
		else if (strcmp(FlashLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new FlashLedEffect<leds, numLeds>(1);
		}
		else if (strcmp(GlowwormLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new GlowwormLedEffect<leds, numLeds>(30);
		}
		else if (strcmp(RainbowLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new RainbowLedEffect<leds, numLeds>(10);
		}
		else if (strcmp(SparklesLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new SparklesLedEffect<leds, numLeds>(20);
		}
		else if (strcmp(ThreeColorLedEffect<leds, numLeds>::name, effectName) == 0)
		{
			delete effect; effect = new ThreeColorLedEffect<leds, numLeds>(30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 });
		}
		else
		{
			return false;
		}

		if (effect != nullptr) effect->start();

		return true;
	};
};


template <CRGB* const leds, const uint16_t numLeds>
const uint8_t DynamicLEDLine<leds, numLeds>::NUM_EFFECTS = 9;

template <CRGB* const leds, const uint16_t numLeds>
const char* const DynamicLEDLine<leds, numLeds>::availableEffects[] =
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
