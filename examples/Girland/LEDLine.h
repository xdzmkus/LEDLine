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

class LEDLine
{
public:

	static const uint8_t NUM_EFFECTS = 8;
	const char* const availableEffects[NUM_EFFECTS] =
	{
		BugsLedEffect::name,
		GlowwormLedEffect::name,
		ColorsLedEffect::name,
		SparklesLedEffect::name,
		RainbowLedEffect::name,
		FlameLedEffect::name,
		FlashLedEffect::name,
		FlagLedEffect::name
	};

	LEDLine(CRGB leds[], uint16_t count) : leds(leds), numLeds(count)
	{
	};
	
	virtual ~LEDLine()
	{
		delete effect;
	};

	virtual bool setEffectByName(const char* effectName)
	{
		if (strcmp(BugsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BugsLedEffect(leds, numLeds, 20);
			return true;
		}
		if (strcmp(GlowwormLedEffect::name, effectName) == 0) {
			delete effect; effect = new GlowwormLedEffect(leds, numLeds, 30);
			return true;
		}
		if (strcmp(ColorsLedEffect::name, effectName) == 0)	{
			delete effect; effect = new ColorsLedEffect(leds, numLeds, 10);
			return true;
		}
		if (strcmp(RainbowLedEffect::name, effectName) == 0) {
			delete effect; effect = new RainbowLedEffect(leds, numLeds, 10);
			return true;
}
		if (strcmp(SparklesLedEffect::name, effectName) == 0) {
			delete effect; effect = new SparklesLedEffect(leds, numLeds, 10);
			return true;
		}
		if (strcmp(FlameLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlameLedEffect(leds, numLeds, 10);
			return true;
		}
		if (strcmp(FlashLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlashLedEffect(leds, numLeds, 1, CRGB::Yellow);
			return true;
		}
		if (strcmp(FlagLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlagLedEffect(leds, numLeds, 30, { CRGB::White, 88, CRGB::Red, 80, CRGB::White, 88 }, 1, 2);
			return true;
		}

		return false;
	};

	virtual void setNextEffect()
	{
		if (effect == nullptr) setEffectByName(availableEffects[0]);

		for (uint8_t idx = 0; idx < NUM_EFFECTS - 1; idx++)
		{
			if (strcmp(availableEffects[idx], static_cast<const char*>(*effect)) == 0)
			{
				setEffectByName(availableEffects[idx + 1]);
				return;
			}
		}

		setEffectByName(availableEffects[0]);
	};

	virtual const char* getEffectName() const { return (effect != nullptr) ? static_cast<const char*>(*effect) : nullptr; };

	virtual void pause() { isOn = false; };
	virtual void resume() { isOn = true; };
	virtual bool paint() { return (!isOn || effect == nullptr) ? false : effect->paint(); };

protected:

	CRGB* const leds;
	const uint16_t numLeds;

	LedEffect* effect = nullptr;

	bool isOn = false;
};


#endif
