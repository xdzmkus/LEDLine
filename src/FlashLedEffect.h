/* 
* FlashLedEffect.h
*
*/

#ifndef __FLASHLEDEFFECT_H__
#define __FLASHLEDEFFECT_H__

#include "ILedEffect.h"

class FlashLedEffect : public ILedEffect
{
public:

	static const char* const name;

protected:

	const CRGB flashColor;
	bool flashState = false;
	
public:
	FlashLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color = CRGB::Black);
	~FlashLedEffect();
	
	void reset() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	FlashLedEffect(const FlashLedEffect&) = delete;
	FlashLedEffect& operator=(const FlashLedEffect&) = delete;
};

#endif //__FLASHLEDEFFECT_H__
