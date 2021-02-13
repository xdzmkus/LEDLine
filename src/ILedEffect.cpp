/*
* ILedEffect.cpp
*
*/

#include "ILedEffect.h"

ILedEffect::ILedEffect(CRGB leds[], uint16_t count, uint16_t Hz)
	: MillisTimer(Hz ? MillisTimer::CLOCKS_IN_SEC / Hz : 0), ILedLine(leds, count), speed(Hz)
{
}

ILedEffect::~ILedEffect()
{
}

void ILedEffect::setId(const EffectID id)
{
	this->id = id;
}

const EffectID ILedEffect::getId() const
{
	return id;
}
