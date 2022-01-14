/*
* ILedEffect.hpp
*
*/

#ifndef _ILEDEFFECT_HPP_
#define _ILEDEFFECT_HPP_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "internal/EffectTimer.hpp"

typedef String LedEffectID;
typedef const char* LedEffectName;

class ILedEffect : public MillisTimer
{
protected:

	const uint16_t speed;

	LedEffectID id;

public:

	ILedEffect(uint16_t Hz = 10) : MillisTimer(Hz ? MillisTimer::CLOCKS_IN_SEC / Hz : 0), speed(Hz)
	{
	};

	virtual ~ILedEffect()
	{
	};

	virtual void paint() = 0;

	virtual operator LedEffectName () const = 0;
	
	virtual void setId(const LedEffectID id)
	{
		this->id = id;
	};

	virtual const LedEffectID getId() const
	{
		return id;
	};
};

#endif
