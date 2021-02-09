/*
* ILedEffect.h
*
*/

#ifndef _ILEDEFFECT_H
#define _ILEDEFFECT_H

#include <IEffectTimer.h>
#include <FastLED.h>

typedef String EffectID;

class ILedEffect : public MillisTimer
{
protected:

	CRGB* const	ledLine;
	const uint16_t numLeds;
	const uint16_t speed;

	EffectID id;

public:

	ILedEffect(CRGB leds[], uint16_t count, uint16_t Hz = 10);
	virtual ~ILedEffect();

	virtual bool paint() = 0;

	virtual operator const char* () const = 0;
	
	virtual void setId(const EffectID id);
	virtual const EffectID getId() const;

protected:

	CRGB getRandomColor() const;
	void fillAllLeds(CRGB color);
	void clearAllLeds();
};

#endif
