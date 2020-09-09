// LEDLine.h

#ifndef _LEDLINE_h
#define _LEDLINE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <FastLED.h>
#include "ILedEffect.h"

class LEDLine
{
protected:

	ILedEffect** effects;
	const uint8_t numEffects;

	uint8_t currentEffect = 0;
	bool isOn = false;

public:

	LEDLine(ILedEffect* effects[], uint8_t numEffects);
	virtual ~LEDLine();

	virtual void saveState(int memIdx);
	virtual void loadState(int memIdx);
	virtual void nextState();

	virtual void pause();
	virtual void resume();

	virtual bool isChanged();
};

#endif
