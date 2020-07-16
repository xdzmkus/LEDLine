/*
* ILedEffect.h
*
*/

#ifndef _LEDEFFECT_h
#define _LEDEFFECT_h

#include <FastLED.h>

class ILedEffect
{
protected:

	CRGB*		ledLine;
	uint16_t	numLeds;

public:

	ILedEffect(CRGB leds[], uint16_t count);
	virtual ~ILedEffect();
	virtual void refresh() = 0;
	
protected:

	uint32_t getPixelColor(uint16_t pixel) const;

	void fillAllLeds(CRGB color) const;
};

#endif
