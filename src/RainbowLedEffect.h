/* 
* RainbowLedEffect.h
*
*/


#ifndef __RAINBOWLEDEFFECT_H__
#define __RAINBOWLEDEFFECT_H__

#include "ILedEffect.h"

class RainbowLedEffect : public ILedEffect
{
private:
	const float k;
	uint8_t hue = 0;

public:
	RainbowLedEffect(CRGB leds[], uint16_t count);
	~RainbowLedEffect();
	virtual void refresh() override;

private:
	RainbowLedEffect( const RainbowLedEffect &c );
	RainbowLedEffect& operator=( const RainbowLedEffect &c );

};

#endif //__RAINBOWLEDEFFECT_H__
