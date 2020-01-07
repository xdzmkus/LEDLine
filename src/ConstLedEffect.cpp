/* 
* ConstLedEffect.cpp
*
*/


#include "ConstLedEffect.h"

// default constructor
ConstLedEffect::ConstLedEffect(CRGB leds[], uint16_t count, CRGB color) : ILedEffect(leds, count), rgb(color)
{
}

// default destructor
ConstLedEffect::~ConstLedEffect()
{
}

void ConstLedEffect::refresh()
{
	fillAllLeds(rgb);
}
