/*
* FlagLedEffect.h
*
*/

#ifndef __FLAGLEDEFFECT_H__
#define __FLAGLEDEFFECT_H__

#include "LedEffect.h"


class FlagLedEffect : public LedEffect
{
public:

	static const char* const name;

protected:

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

	CRGB fadeForRGB1;
	CRGB fadeForRGB2;
	CRGB fadeForRGB3;
	uint8_t pulses;
	uint16_t restOfFade;

public:
	FlagLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, FLAG flag, uint8_t pulseTime = 1, uint8_t pulseCount = 2);
	~FlagLedEffect();

	void init() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	FlagLedEffect(const FlagLedEffect&) = delete;
	FlagLedEffect& operator=(const FlagLedEffect&) = delete;

};

#endif //__FLAGLEDEFFECT_H__
