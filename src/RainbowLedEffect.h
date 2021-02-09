/* 
* RainbowLedEffect.h
*
*/

#ifndef __RAINBOWLEDEFFECT_H__
#define __RAINBOWLEDEFFECT_H__

#include "ILedEffect.h"

class RainbowLedEffect : public ILedEffect
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
	RainbowLedEffect(const RainbowLedEffect&) = delete;
	RainbowLedEffect& operator=(const RainbowLedEffect&) = delete;
};

#endif //__RAINBOWLEDEFFECT_H__
