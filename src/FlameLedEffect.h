/* 
* FlameLedEffect.h
*
*/

#ifndef __FLAMELEDEFFECT_H__
#define __FLAMELEDEFFECT_H__

#include "ILedEffect.h"

class FlameLedEffect : public ILedEffect
{
private:
	uint8_t* heatMap;
	bool fireReversed;
	CRGBPalette16 gPal;

public:
	FlameLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, bool reversed = false);
	~FlameLedEffect();
	
	bool paint() override;

private:
	FlameLedEffect(const FlameLedEffect&);
	FlameLedEffect& operator=(const FlameLedEffect&);

};

#endif //__FLAMELEDEFFECT_H__