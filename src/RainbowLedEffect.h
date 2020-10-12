/* 
* RainbowLedEffect.h
*
*/

#ifndef __RAINBOWLEDEFFECT_H__
#define __RAINBOWLEDEFFECT_H__

#include "LedEffect.h"

class RainbowLedEffect : public LedEffect
{
public:

	static const char* const name;

protected:

	const float k;
	uint8_t hue = 0;

public:
	RainbowLedEffect(CRGB leds[], uint16_t count, uint16_t Hz);
	~RainbowLedEffect();
	
	void reset() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	RainbowLedEffect(const RainbowLedEffect&);
	RainbowLedEffect& operator=(const RainbowLedEffect&);
};

#endif //__RAINBOWLEDEFFECT_H__
