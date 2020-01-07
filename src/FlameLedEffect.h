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
	FlameLedEffect(CRGB leds[], uint16_t count, bool reversed = false);
	~FlameLedEffect();
	virtual void refresh() override;

private:
	FlameLedEffect( const FlameLedEffect &c );
	FlameLedEffect& operator=( const FlameLedEffect &c );

};

#endif //__FLAMELEDEFFECT_H__
