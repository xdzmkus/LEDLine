/*
* LEDLine.h
*
*/

#ifndef _LEDLINE_H_
#define _LEDLINE_H_

#include "internal/ILedEffect.hpp"

class LEDLine
{
private:
	
	const char* const OFF = "OFF";

protected:

	ILedEffect* effect = nullptr;

public:

	LEDLine();

	virtual ~LEDLine();

	virtual uint8_t howManyEffects() const = 0;

	virtual const char* const* getAllEffectsNames() const = 0;

	virtual bool setEffectByName(const char* effectName) = 0;

	virtual bool setEffectByIdx(uint8_t idx);

	virtual bool setNextEffect();

	virtual const char* getEffectName() const;

	virtual uint8_t getEffectIdx() const;

	virtual void turnOn();

	virtual void turnOff();

	virtual bool isOn() const;

	virtual bool refresh();

	virtual const char* getState() const;
};

#endif
