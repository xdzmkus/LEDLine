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
#include "UniversalLEDLineEffects.h"

template <CRGB* const leds, const uint16_t numLeds>
class StaticLEDLine : public LEDLine
{
private:

	static const uint8_t NUM_EFFECTS = 9;

	static BouncingBallsLedEffect<leds, numLeds, NUM_BALLS> bouncingBallsEffect;
	static BugsLedEffect<leds, numLeds, NUM_BUGS> bugsEffect;
	static ColorsLedEffect<leds, numLeds> colorsEffect;
	static FlameLedEffect<leds, numLeds> flameEffect;
	static FlashLedEffect<leds, numLeds> flashEffect;
	static GlowwormLedEffect<leds, numLeds> glowwormEffect;
	static RainbowLedEffect<leds, numLeds> rainbowEffect;
	static SparklesLedEffect<leds, numLeds> sparklesEffect;
	static ThreeColorLedEffect<leds, numLeds> threeColorEffect;

	ILedEffect* effects[NUM_EFFECTS] =
	{
		&bouncingBallsEffect,
		&bugsEffect,
		&colorsEffect,
		&flameEffect,
		&flashEffect,
		&glowwormEffect,
		&rainbowEffect,
		&sparklesEffect,
		&threeColorEffect
	};

	LedEffectName const availableEffects[NUM_EFFECTS] =
	{ 
		bouncingBallsEffect.name,
		bugsEffect.name,
		colorsEffect.name,
		flameEffect.name,
		flashEffect.name,
		glowwormEffect.name,
		rainbowEffect.name,
		sparklesEffect.name,
		threeColorEffect.name
	};
	
public:

	StaticLEDLine()
	{
	};

	virtual ~StaticLEDLine()
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
		for (uint8_t idx = 0; idx < NUM_EFFECTS; ++idx)
		{
			if (strcmp(*(effects[idx]), effectName) == 0)
			{
				activeEffect = effects[idx];
				activeEffect->start();
				return true;
			}
		}

		return false;
	};
};


template <CRGB* const leds, const uint16_t numLeds>
BouncingBallsLedEffect<leds, numLeds, NUM_BALLS> StaticLEDLine<leds, numLeds>::bouncingBallsEffect(50);

template <CRGB* const leds, const uint16_t numLeds>
BugsLedEffect<leds, numLeds, NUM_BUGS> StaticLEDLine<leds, numLeds>::bugsEffect(20);

template <CRGB* const leds, const uint16_t numLeds>
ColorsLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::colorsEffect(10);

template <CRGB* const leds, const uint16_t numLeds>
FlameLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::flameEffect(10);

template <CRGB* const leds, const uint16_t numLeds>
FlashLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::flashEffect(1);

template <CRGB* const leds, const uint16_t numLeds>
GlowwormLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::glowwormEffect(30);

template <CRGB* const leds, const uint16_t numLeds>
RainbowLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::rainbowEffect(10);

template <CRGB* const leds, const uint16_t numLeds>
SparklesLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::sparklesEffect(20);

template <CRGB* const leds, const uint16_t numLeds>
ThreeColorLedEffect<leds, numLeds> StaticLEDLine<leds, numLeds>::threeColorEffect(30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 });



#endif
