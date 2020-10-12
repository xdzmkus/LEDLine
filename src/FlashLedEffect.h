/* 
* FlashLedEffect.h
*
*/

#ifndef __FLASHLEDEFFECT_H__
#define __FLASHLEDEFFECT_H__

#include "LedEffect.h"

class FlashLedEffect : public LedEffect
{
public:

	static const char* const name;

protected:

	CRGB		flashColor;
	bool		flashState = false;
	
public:
	FlashLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color);
	~FlashLedEffect();
	
	void reset() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	FlashLedEffect(const FlashLedEffect&);
	FlashLedEffect& operator=(const FlashLedEffect&);
};

#endif //__FLASHLEDEFFECT_H__
