/*
* ILedEffect.h
*
*/

#ifndef _LEDEFFECT_h
#define _LEDEFFECT_h

#include <FastLED.h>

class LedEffect
{
private:

	bool state = false;
	unsigned long interval = 0;
	unsigned long timer = 0;

protected:

	CRGB* const ledLine;
	const uint16_t numLeds;

public:

	LedEffect(CRGB leds[], uint16_t count, uint16_t Hz = 10);
	virtual ~LedEffect();

	virtual void reset();
	virtual bool paint();

	virtual operator const char* () const = 0;
	
protected:

	uint32_t getPixelColor(uint16_t pixel) const;

	void fillAllLeds(CRGB color) const;
};

#endif
