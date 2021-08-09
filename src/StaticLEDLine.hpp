/*
* StaticLEDLine.hpp
*
*/

#ifndef _STATICLEDLINE_HPP_
#define _STATICLEDLINE_HPP_

#define NUM_BALLS 5
#define NUM_BUGS 15

#include "LEDLine.h"
#include "StaticLEDLineEffects.h"

template <CRGB* const leds, const uint16_t numLeds>
class StaticLEDLine : public LEDLine
{
private:

	static const uint8_t NUM_EFFECTS = 9;

	BouncingBallsLedEffect<leds, numLeds, NUM_BALLS> eff1;
	BugsLedEffect<leds, numLeds, NUM_BUGS> eff2;
	ColorsLedEffect<leds, numLeds> eff3;
	FlameLedEffect<leds, numLeds> eff4;
	FlashLedEffect<leds, numLeds> eff5;
	GlowwormLedEffect<leds, numLeds> eff6;
	RainbowLedEffect<leds, numLeds> eff7;
	SparklesLedEffect<leds, numLeds> eff8;
	ThreeColorLedEffect<leds, numLeds> eff9;

	const char* const availableEffects[NUM_EFFECTS] = { eff1.name, eff2.name, eff3.name, eff4.name, eff5.name, eff6.name, eff7.name, eff8.name, eff9.name };

	ILedEffect* const effects[NUM_EFFECTS] = { &eff1, &eff2, &eff3, &eff4, &eff5, &eff6, &eff7, &eff8, &eff9 };

public:

	StaticLEDLine()	:
		eff1(50),
		eff2(20),
		eff3(10),
		eff4(10),
		eff5(1),
		eff6(30),
		eff7(10),
		eff8(20),
		eff9(30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 })
	{
	};

	virtual ~StaticLEDLine()
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
		for (uint8_t idx = 0; idx < NUM_EFFECTS; ++idx)
		{
			if (strcmp(*(effects[idx]), effectName) == 0)
			{
				effect = effects[idx];
				effect->start();
				return true;
			}
		}

		return false;
	};
};

/*
template <CRGB* const leds, const uint16_t numLeds>
const uint8_t StaticLEDLine<leds, numLeds>::NUM_EFFECTS = 9;
*/

#endif
