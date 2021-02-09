/*
* ThreeColorLedEffect.h
*
*/

#ifndef __THREECOLORLEDEFFECT_H__
#define __THREECOLORLEDEFFECT_H__

#include "ILedEffect.h"


class ThreeColorLedEffect : public ILedEffect
{
public:

	static const char* const name;

protected:

	const struct THREECOLOR
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
	ThreeColorLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, THREECOLOR flag, uint8_t pulseTime = 1, uint8_t pulseCount = 2);
	~ThreeColorLedEffect();

	void reset() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	ThreeColorLedEffect(const ThreeColorLedEffect&) = delete;
	ThreeColorLedEffect& operator=(const ThreeColorLedEffect&) = delete;

};

#endif
