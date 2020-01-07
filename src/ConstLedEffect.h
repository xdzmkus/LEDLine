/* 
* ConstLedEffect.h
*
*/


#ifndef __CONSTLEDEFFECT_H__
#define __CONSTLEDEFFECT_H__

#include "ILedEffect.h"

class ConstLedEffect : public ILedEffect
{
private:
	CRGB rgb;
	
public:
	ConstLedEffect(CRGB leds[], uint16_t count, CRGB color = CRGB::Black);
	~ConstLedEffect();
	
	virtual void refresh();

private:
	ConstLedEffect( const ConstLedEffect &c );
	ConstLedEffect& operator=( const ConstLedEffect &c );

};

#endif
