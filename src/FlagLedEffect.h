/* 
* FlagLedEffect.h
*
*/


#ifndef __FLAGLEDEFFECT_H__
#define __FLAGLEDEFFECT_H__

#include "ILedEffect.h"

class FlagLedEffect : public ILedEffect
{
private:
	CRGB rgb1;
    uint16_t count1;
	CRGB rgb2;
    uint16_t count2;	
	CRGB rgb3;
    uint16_t count3;
	
public:
	FlagLedEffect(CRGB leds[], uint16_t count, 
				  CRGB firstColor = CRGB::White, uint16_t firstColorCount = 3, 
				  CRGB secondColor = CRGB::Red, uint16_t secondColorCount = 5, 
				  CRGB thirdColor = CRGB::White, uint16_t thirdColorCount = 3);
	~FlagLedEffect();

	virtual void refresh() override;

private:
	FlagLedEffect( const FlagLedEffect &c );
	FlagLedEffect& operator=( const FlagLedEffect &c );

};

#endif //__FLAGLEDEFFECT_H__
