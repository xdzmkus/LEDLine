/*
* LedLine.h
*
*/

#ifndef _LEDLINE_H_
#define _LEDLINE_H_

#include <FastLED.h>
#include "ILedEffect.h"

class LedLine
{
private:

	static const uint8_t NUM_EFFECTS;
	static const char* availableEffects[];

public:

	LedLine(CRGB leds[], uint16_t count, bool start = false);

	virtual ~LedLine();

	virtual uint8_t getAllEffectsNumber() const;

	virtual const char** getAllEffectsNames() const;

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
