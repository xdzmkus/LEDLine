/*
* ThreeColorLedEffect.hpp
*
*/

#ifndef __THREECOLORLEDEFFECT_HPP__
#define __THREECOLORLEDEFFECT_HPP__

#include "internal/ILedLine.hpp"
#include "internal/ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class ThreeColorLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static const char* const name;

private:

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

	ThreeColorLedEffect(uint16_t Hz, THREECOLOR flag, uint8_t pulseTime = 1, uint8_t pulseCount = 2);
	~ThreeColorLedEffect();

	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:

	ThreeColorLedEffect(const ThreeColorLedEffect&) = delete;
	ThreeColorLedEffect& operator=(const ThreeColorLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const ThreeColorLedEffect<ledLine, numLeds>::name = "THREECOLOR";

template <CRGB* const ledLine, const uint16_t numLeds>
ThreeColorLedEffect<ledLine, numLeds>::ThreeColorLedEffect(uint16_t Hz, THREECOLOR flag, uint8_t pulseTime, uint8_t pulseCount)
	: ILedEffect(Hz), flag(flag), timesToFade(Hz* pulseTime), pulseCount(pulseCount)
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
ThreeColorLedEffect<ledLine, numLeds>::~ThreeColorLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void ThreeColorLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	ILedLine<ledLine, numLeds>::clearAllLeds();

	uint16_t position = 0;

	while (position < numLeds)
	{
		for (uint16_t firstColorCount = 0; position < numLeds && firstColorCount < flag.count1; firstColorCount++)
			ledLine[position++] = flag.rgb1;
		for (uint16_t secondColorCount = 0; position < numLeds && secondColorCount < flag.count2; secondColorCount++)
			ledLine[position++] = flag.rgb2;
		for (uint16_t thirdColorCount = 0; position < numLeds && thirdColorCount < flag.count3; thirdColorCount++)
			ledLine[position++] = flag.rgb3;
	}

	if (timesToFade != 0)
	{
		fadeForRGB1 = CRGB(1 + flag.rgb1.r / timesToFade, 1 + flag.rgb1.g / timesToFade, 1 + flag.rgb1.b / timesToFade);
		fadeForRGB2 = CRGB(1 + flag.rgb2.r / timesToFade, 1 + flag.rgb2.g / timesToFade, 1 + flag.rgb2.b / timesToFade);
		fadeForRGB3 = CRGB(1 + flag.rgb3.r / timesToFade, 1 + flag.rgb3.g / timesToFade, 1 + flag.rgb3.b / timesToFade);
	}

	restOfFade = timesToFade;
	pulses = pulseCount;
}

template <CRGB* const ledLine, const uint16_t numLeds>
void ThreeColorLedEffect<ledLine, numLeds>::paint()
{
	if (timesToFade == 0)
		return;

	// black(skipped) pulse?
	if (pulses == 0)
	{
		if (restOfFade == 0)
		{
			pulses = pulseCount;
			restOfFade = timesToFade;
		}
		else
		{
			restOfFade--;
		}
		return;
	}

	// almost black (pulse done)?
	if (restOfFade == 0)
	{
		restOfFade = timesToFade;
		pulses--;
		ILedLine<ledLine, numLeds>::clearAllLeds();
		return;
	}

	uint16_t position = 0;

	while (position < numLeds)
	{
		if (restOfFade == timesToFade)
		{
			// show original flag
			for (uint16_t firstColorCount = 0; position < numLeds && firstColorCount < flag.count1; firstColorCount++)
				ledLine[position++] = flag.rgb1;
			for (uint16_t secondColorCount = 0; position < numLeds && secondColorCount < flag.count2; secondColorCount++)
				ledLine[position++] = flag.rgb2;
			for (uint16_t thirdColorCount = 0; position < numLeds && thirdColorCount < flag.count3; thirdColorCount++)
				ledLine[position++] = flag.rgb3;
		}
		else
		{
			// fade a bit
			for (uint16_t firstColorCount = 0; position < numLeds && firstColorCount < flag.count1; firstColorCount++)
				ledLine[position++] -= fadeForRGB1;
			for (uint16_t secondColorCount = 0; position < numLeds && secondColorCount < flag.count2; secondColorCount++)
				ledLine[position++] -= fadeForRGB2;
			for (uint16_t thirdColorCount = 0; position < numLeds && thirdColorCount < flag.count3; thirdColorCount++)
				ledLine[position++] -= fadeForRGB3;
		}
	}

	restOfFade--;
}

#endif
