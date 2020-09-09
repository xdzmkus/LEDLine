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

	const struct FLAG
	{
		CRGB rgb1;
		uint16_t count1;
		CRGB rgb2;
		uint16_t count2;
		CRGB rgb3;
		uint16_t count3;
	} flag;

	static const uint8_t STEP_WIDE = 20;
	const int8_t step_line[STEP_WIDE] = { 0,0,0,0, -1,1,-1,1,-1,1, 0,0,0,0, 1,-1,1,-1,1,-1 };
	const uint8_t step_count;

	uint16_t step_position = 0;
	bool step_direction = true;

public:
	FlagLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, FLAG flag, uint8_t step = 0);
	~FlagLedEffect();

	void reset() override;
	bool paint() override;

private:
	FlagLedEffect(const FlagLedEffect&);
	FlagLedEffect& operator=(const FlagLedEffect&) {};

};

#endif //__FLAGLEDEFFECT_H__
