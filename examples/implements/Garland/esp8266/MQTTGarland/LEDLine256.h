// LEDLine256.h

#ifndef _LEDLINE_256_H_
#define _LEDLINE_256_H_

#include <FastLED.h>

#include "LEDLine.h"
#include "BouncingBallsLedEffect.h"
#include "BugsLedEffect.h"
#include "ColorsLedEffect.h"
#include "FlameLedEffect.h"
#include "FlashLedEffect.h"
#include "GlowwormLedEffect.h"
#include "RainbowLedEffect.h"
#include "SparklesLedEffect.h"
#include "ThreeColorLedEffect.h"

class LEDLine256 : public LEDLine
{
public:

	LEDLine256(CRGB leds[], uint16_t count) : LEDLine(leds, count)
	{
	};

	bool setEffectByName(const char* effectName) override
	{
		bool restart = isOn();

		if (strcmp(BouncingBallsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BouncingBallsLedEffect(leds, numLeds, 50, random8(0, 20));
		}
		else if (strcmp(BugsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BugsLedEffect(leds, numLeds, 20, random8(0, 40));
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
			delete effect; effect = new ThreeColorLedEffect(leds, numLeds, 30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 });
		}
		else {
			return false;
		}

		if (restart)
		{
			turnOn();
		}

		return true;
	};
};


#endif
