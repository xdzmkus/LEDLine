/*
* LEDLine.h
*
*/

#ifndef _LEDLINE_H_
#define _LEDLINE_H_

#include <FastLED.h>
#include "ILedEffect.h"

class LEDLine
{
private:

	static const uint8_t NUM_EFFECTS;
	static const char* availableEffects[];

public:

	LEDLine(CRGB leds[], uint16_t count, bool start = false);

	virtual ~LEDLine();

	virtual uint8_t getAllEffectsNumber() const;

	virtual const char* const* getAllEffectsNames() const;

	virtual const char* getEffectName() const;

	virtual uint8_t getEffectIdx() const;

	virtual bool setEffectByName(const char* effectName);

	virtual bool setEffectByIdx(uint8_t idx);
	
	virtual bool setNextEffect();

	virtual void pause();

	virtual void resume();

	virtual bool refresh() const;

	virtual bool isRunning() const;

protected:

	CRGB* const leds;
	const uint16_t numLeds;

	ILedEffect* effect = nullptr;

	bool isOn = false;
};

#endif
