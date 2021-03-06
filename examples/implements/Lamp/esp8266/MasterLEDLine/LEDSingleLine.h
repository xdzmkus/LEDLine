// LEDSingleLine.h

#ifndef _LEDSINGLELINE_H_
#define _LEDSINGLELINE_H_

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

class LEDLine8leds : public LEDLine
{
public:
	LEDLine8leds(CRGB leds[], uint16_t count) : LEDLine(leds, count)
	{
	};

	bool setEffectByName(const char* effectName) override
	{
		bool restart = isOn();

		if (strcmp(BouncingBallsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BouncingBallsLedEffect(leds, numLeds, 50, 2);
		}
		else if (strcmp(BugsLedEffect::name, effectName) == 0) {
			delete effect; effect = new BugsLedEffect(leds, numLeds, random8(10, 30), 2);
		}
		else if (strcmp(GlowwormLedEffect::name, effectName) == 0) {
			delete effect; effect = new GlowwormLedEffect(leds, numLeds, random8(10, 30));
		}
		else if (strcmp(ThreeColorLedEffect::name, effectName) == 0) {
			delete effect; effect = new ThreeColorLedEffect(leds, numLeds, 30, { CRGB::White, 2, CRGB::Red, 4, CRGB::White, 2 });
		}
		else {
			return LEDLine::setEffectByName(effectName);
		}

		if (restart)
		{
			turnOn();
		}

		return true;
	};
};

#endif
