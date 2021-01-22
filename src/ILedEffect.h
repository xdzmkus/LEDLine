/*
* ILedEffect.h
*
*/

#ifndef _ILEDEFFECT_h
#define _ILEDEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <IEffectTimer.h>
#include <FastLED.h>

class ILedEffect :  public MillisTimer
{
protected:

	CRGB* const ledLine;
	const uint16_t numLeds;
	const uint16_t speed;

public:

	ILedEffect(CRGB leds[], uint16_t count, uint16_t Hz = 10);
	virtual ~ILedEffect();

	virtual void init() = 0;
	virtual bool paint() = 0;

	virtual operator const char* () const = 0;
	
protected:

	CRGB getRandomColor() const;
	void fillAllLeds(CRGB color);
	void clearAllLeds();
};

#endif
