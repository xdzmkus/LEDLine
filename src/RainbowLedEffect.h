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
	RainbowLedEffect(CRGB leds[], uint16_t count, uint16_t Hz);
	~RainbowLedEffect();
	
	void reset() override;
	bool paint() override;

private:
	RainbowLedEffect(const RainbowLedEffect&);
	RainbowLedEffect& operator=(const RainbowLedEffect&);
};

#endif //__RAINBOWLEDEFFECT_H__
