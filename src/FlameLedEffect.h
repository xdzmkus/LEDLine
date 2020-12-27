/* 
* FlameLedEffect.h
*
*/

#ifndef __FLAMELEDEFFECT_H__
#define __FLAMELEDEFFECT_H__

#include "LedEffect.h"

class FlameLedEffect : public LedEffect
{
public:

	static const char* const name;

protected:

	uint8_t* heatMap = nullptr;
	const bool fireReversed;
	const CRGBPalette16 gPal;

public:
	FlameLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, bool reversed = false);
	~FlameLedEffect();
	
	void init() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	FlameLedEffect(const FlameLedEffect&) = delete;
	FlameLedEffect& operator=(const FlameLedEffect&) = delete;

};

#endif //__FLAMELEDEFFECT_H__
