/*
* ILedEffect.hpp
*
*/

#ifndef _ILEDEFFECT_HPP_
#define _ILEDEFFECT_HPP_

#include "EffectTimer.hpp"

typedef String EffectID;

class ILedEffect : public MillisTimer
{
protected:

	const uint16_t speed;

	EffectID id;

public:

	ILedEffect(uint16_t Hz = 10) : MillisTimer(Hz ? MillisTimer::CLOCKS_IN_SEC / Hz : 0), speed(Hz)
	{
	};

	virtual ~ILedEffect()
	{
	};

	virtual void paint() = 0;

	virtual operator const char* () const = 0;
	
	virtual void setId(const EffectID id)
	{
		this->id = id;
	};

	virtual const EffectID getId() const
	{
		return id;
	};
};

#endif
