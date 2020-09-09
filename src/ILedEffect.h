/*
* ILedEffect.h
*
*/

#ifndef _LEDEFFECT_h
#define _LEDEFFECT_h

#include <FastLED.h>
#include <GyverTimer.h>

class ILedEffect
{
protected:

	CRGB* const ledLine;
	const uint16_t numLeds;

	GTimer_ms effectTimer;

public:

	ILedEffect(CRGB leds[], uint16_t count, uint16_t Hz = 10);
	virtual ~ILedEffect();

	virtual void reset();
	virtual bool paint() = 0;
	
protected:

	uint32_t getPixelColor(uint16_t pixel) const;

	void fillAllLeds(CRGB color) const;
};

#endif
