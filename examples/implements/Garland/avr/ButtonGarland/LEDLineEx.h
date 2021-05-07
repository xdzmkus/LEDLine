// LEDLineEx.h

#ifndef _LEDLINE_EX_H_
#define _LEDLINE_EX_H_

#include <FastLED.h>

#include "LEDLine.h"
#include "ThreeColorLedEffect.h"

class LEDLineEx : public LEDLine
{
public:

	LEDLineEx(CRGB leds[], uint16_t count) : LEDLine(leds, count)
	{
	};

	bool setEffectByName(const char* effectName) override
	{
		bool restart = isOn();

		if (strcmp(ThreeColorLedEffect::name, effectName) == 0) {
			delete effect; effect = new ThreeColorLedEffect(leds, numLeds, 30, { CRGB::White, 3, CRGB::Red, 2, CRGB::White, 3 });
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
