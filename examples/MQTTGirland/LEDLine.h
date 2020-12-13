// LEDLine.h

#ifndef _LEDLINE_h
#define _LEDLINE_h

#include <FastLED.h>

#include "LedEffect.h"
#include "FlashLedEffect.h"
#include "GlowwormLedEffect.h"
#include "ColorsLedEffect.h"
#include "RainbowLedEffect.h"
#include "SparklesLedEffect.h"
#include "BugsLedEffect.h"
#include "FlameLedEffect.h"
#include "FlagLedEffect.h"
#include "BouncingBallsLedEffect.h"

class LEDLine
{
public:

	static const uint8_t NUM_EFFECTS = 9;
	const char* const availableEffects[NUM_EFFECTS] =
	{
		BugsLedEffect::name,
		GlowwormLedEffect::name,
		ColorsLedEffect::name,
		SparklesLedEffect::name,
		RainbowLedEffect::name,
		FlameLedEffect::name,
		FlashLedEffect::name,
		FlagLedEffect::name,
		BouncingBallsLedEffect::name
	};

	LEDLine(CRGB leds[], uint16_t count) : leds(leds), numLeds(count), isOn(false)
	{
	};

	~LEDLine()
	{
		delete effect;
	};

	bool setEffectByName(const char* effectName)
	{
		if (strcmp(BugsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BugsLedEffect(leds, numLeds, 20);
		}
		else if (strcmp(GlowwormLedEffect::name, effectName) == 0) {
			delete effect; effect = new GlowwormLedEffect(leds, numLeds, 30);
		}
		else if (strcmp(ColorsLedEffect::name, effectName) == 0) {
			delete effect; effect = new ColorsLedEffect(leds, numLeds, 10);
		}
		else if (strcmp(RainbowLedEffect::name, effectName) == 0) {
			delete effect; effect = new RainbowLedEffect(leds, numLeds, 10);
		}
		else if (strcmp(SparklesLedEffect::name, effectName) == 0) {
			delete effect; effect = new SparklesLedEffect(leds, numLeds, 20);
		}
		else if (strcmp(FlameLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlameLedEffect(leds, numLeds, 10);
		}
		else if (strcmp(FlashLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlashLedEffect(leds, numLeds, 1);
		}
		else if (strcmp(FlagLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlagLedEffect(leds, numLeds, 30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 }, 1, 2);
		}
		else if (strcmp(BouncingBallsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BouncingBallsLedEffect(leds, numLeds, 50);
		}
		else {
			return false;
		}

		isOn = true;
		return true;

	};

	bool setNextEffect()
	{
		if (effect != nullptr)
		{
			for (uint8_t idx = 0; idx < NUM_EFFECTS - 1; idx++)
			{
				if (strcmp(availableEffects[idx], static_cast<const char*>(*effect)) == 0)
				{
					return setEffectByName(availableEffects[idx + 1]);
				}
			}
		}

		// first one by default
		return setEffectByName(availableEffects[0]);
	};

	const char* getEffectName() const
	{
		return (effect != nullptr) ? static_cast<const char*>(*effect) : nullptr;
	};

	void pause()
	{
		isOn = false;
		if (effect != nullptr) effect->stop();
	};
	void resume()
	{
		isOn = true;
		if (effect != nullptr) effect->start();
	};
	bool paint()
	{
		return (!isOn || effect == nullptr) ? false : effect->paint();
	};
	bool isRunning()
	{
		return isOn;
	};

protected:

	CRGB* const leds;
	const uint16_t numLeds;

	LedEffect* effect = nullptr;
	bool isOn;
};


#endif
