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

	const uint16_t timesToFade;
	const uint8_t pulseCount;

	uint8_t fadeForRGB1;
	uint8_t fadeForRGB2;
	uint8_t fadeForRGB3;
	uint8_t pulses;
	uint16_t restOfFade;

public:
	FlagLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, FLAG flag, uint8_t pulseTime = 1, uint8_t pulseCount = 2);
	~FlagLedEffect();

	void reset() override;
	bool paint() override;

private:
	FlagLedEffect(const FlagLedEffect&);
	FlagLedEffect& operator=(const FlagLedEffect&) {};

};

#endif //__FLAGLEDEFFECT_H__
