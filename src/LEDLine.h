/*
* LEDLine.h
*
*/

#ifndef _LEDLINE_H_
#define _LEDLINE_H_

#include "ILedEffect.hpp"

typedef const char* LedState;

class LEDLine
{
private:
	
	LedState const OFF = "OFF";

protected:

	ILedEffect* activeEffect = nullptr;

public:

	LEDLine();

	virtual ~LEDLine();

	virtual uint8_t howManyEffects() const = 0;

	virtual LedEffectName const* getAllEffectsNames() const = 0;

	virtual bool setEffectByName(LedEffectName effectName) = 0;

	virtual bool setEffectByIdx(uint8_t idx);

	virtual bool setNextEffect();

	virtual LedEffectName getEffectName() const;

	virtual uint8_t getEffectIdx() const;

	virtual void turnOn();

	virtual void turnOff();

	virtual bool isOn() const;

	virtual bool refresh();

	virtual LedState getState() const;
};

#endif
