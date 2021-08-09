/* 
* FlameLedEffect.hpp
*
*/

#ifndef __FLAMELEDEFFECT_HPP__
#define __FLAMELEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class FlameLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{
public:

	static const char* const name;

private:

	uint8_t heatMap[numLeds];
	const bool fireReversed;
	const CRGBPalette16 gPal;

public:

	FlameLedEffect(uint16_t Hz, bool reversed = false);
	~FlameLedEffect();
	
	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:

	FlameLedEffect(const FlameLedEffect&) = delete;
	FlameLedEffect& operator=(const FlameLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const FlameLedEffect<ledLine, numLeds>::name = "FLAME";

template <CRGB* const ledLine, const uint16_t numLeds>
FlameLedEffect<ledLine, numLeds>::FlameLedEffect(uint16_t Hz, bool reversed)
	: ILedEffect(Hz), fireReversed(reversed), gPal(HeatColors_p)
{
	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
FlameLedEffect<ledLine, numLeds>::~FlameLedEffect()
{
}

template <CRGB* const ledLine, const uint16_t numLeds>
void FlameLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();
	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void FlameLedEffect<ledLine, numLeds>::paint()
{
	// Step 1.  Cool down every cell a little
	for (uint16_t i = 0; i < numLeds; i++)
	{
		heatMap[i] = qsub8(heatMap[i], random(0, 255 / numLeds + 3));
	}

	// Step 2.  heatMap from each cell drifts 'up' and diffuses a little
	for (uint16_t k = numLeds - 1; k > 2; k--)
	{
		heatMap[k] = (heatMap[k - 1] + heatMap[k - 2] + heatMap[k - 3]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heatMap near the bottom
	// What chance (out of 255) is there that a new spark will be lit?
	if (random8() < 64)
	{
		uint8_t y = random(max(3, numLeds / 4));
		heatMap[y] = qadd8(heatMap[y], random(160, 255));
	}

	// Step 4.  Map from heatMap cells to LED colors
	for (uint16_t j = 0; j < numLeds; j++)
	{
		// Scale the heatMap value from 0-255 down to 0-240 for best results with color palettes.
		CRGB color = ColorFromPalette(gPal, scale8(heatMap[j], 240));
		uint16_t pixelnumber = fireReversed ? (numLeds - 1 - j) : j;
		ledLine[pixelnumber] = color;
	}
}

#endif
