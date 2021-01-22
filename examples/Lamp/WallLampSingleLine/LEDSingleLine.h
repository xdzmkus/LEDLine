// LEDSingleLine.h

#ifndef _LEDSINGLELINE_H_
#define _LEDSINGLELINE_H_

#include <FastLED.h>

#include "LedLine.h"
#include "BouncingBallsLedEffect.h"
#include "BugsLedEffect.h"
#include "ColorsLedEffect.h"
#include "FlameLedEffect.h"
#include "FlashLedEffect.h"
#include "GlowwormLedEffect.h"
#include "RainbowLedEffect.h"
#include "SparklesLedEffect.h"
#include "ThreeColorLedEffect.h"

class LEDLine17leds : public LedLine
{
public:
	LEDLine17leds(CRGB leds[], uint16_t count) : LedLine(leds, count)
	{
		setEffectByIdx(0);
	};

	bool setEffectByName(const char* effectName) override
	{
		if (strcmp(BouncingBallsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BouncingBallsLedEffect(leds, numLeds, 50, 3);
		}
		else if (strcmp(BugsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BugsLedEffect(leds, numLeds, 20, 3);
		}
		else if (strcmp(ColorsLedEffect::name, effectName) == 0) {
			delete effect; effect = new ColorsLedEffect(leds, numLeds, 10);
		}
		else if (strcmp(FlameLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlameLedEffect(leds, numLeds, 10);
		}
		else if (strcmp(FlashLedEffect::name, effectName) == 0) {
			delete effect; effect = new FlashLedEffect(leds, numLeds, 1);
		}
		else if (strcmp(GlowwormLedEffect::name, effectName) == 0) {
			delete effect; effect = new GlowwormLedEffect(leds, numLeds, 30);
		}
		else if (strcmp(RainbowLedEffect::name, effectName) == 0) {
			delete effect; effect = new RainbowLedEffect(leds, numLeds, 10);
		}
		else if (strcmp(SparklesLedEffect::name, effectName) == 0) {
			delete effect; effect = new SparklesLedEffect(leds, numLeds, 20);
		}
		else if (strcmp(ThreeColorLedEffect::name, effectName) == 0) {
			delete effect; effect = new ThreeColorLedEffect(leds, numLeds, 30, { CRGB::White, 5, CRGB::Red, 7, CRGB::White, 5 });
		}
		else {
			return false;
		}

		return true;
	};
};

#endif
