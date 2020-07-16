/* 
* ConstLedEffect.cpp
*
*/


#include "ConstLedEffect.h"

ConstLedEffect::ConstLedEffect(CRGB leds[], uint16_t count, CRGB color)
	: ILedEffect(leds, count), rgb(color)
{
}

ConstLedEffect::~ConstLedEffect()
{
}

void ConstLedEffect::refresh()
{
	fillAllLeds(rgb);
}
