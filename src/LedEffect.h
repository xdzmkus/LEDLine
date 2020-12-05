/*
* ILedEffect.h
*
*/

#ifndef _LEDEFFECT_h
#define _LEDEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <FastLED.h>
#include <Denel.h>

using namespace denel;

class LedEffect :  public MillisTimer
{
protected:

	CRGB* const ledLine;
	const uint16_t numLeds;

public:

	LedEffect(CRGB leds[], uint16_t count, uint16_t Hz = 10);
	virtual ~LedEffect();

	virtual void init();
	virtual bool paint() = 0;

	virtual operator const char* () const = 0;
	
protected:

	uint32_t getPixelColor(uint16_t pixel) const;
	CRGB getRandomColor() const;

	void fillAllLeds(CRGB color) const;
};

#endif
