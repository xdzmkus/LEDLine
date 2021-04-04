/*
* FlameLedEffect.cpp
*
*/

#include "FlameLedEffect.h"

const char* const FlameLedEffect::name = "FLAME";

FlameLedEffect::FlameLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, bool reversed)
	: ILedLine(leds, count), ILedEffect(Hz), fireReversed(reversed), gPal(HeatColors_p)
{
	heatMap = new uint8_t[count];

	reset();
}

FlameLedEffect::~FlameLedEffect()
{
	if (heatMap != nullptr)
	{
		delete[] heatMap;
		heatMap = nullptr;
	}
}

void FlameLedEffect::reset()
{
	ILedEffect::reset();
	clearAllLeds();
}

void FlameLedEffect::paint()
{
	if (heatMap == nullptr)
		return;

	// Step 1.  Cool down every cell a little
	for (uint16_t i = 0; i < numLeds; i++)
	{
		heatMap[i] = qsub8(heatMap[i], random8(0, 255/numLeds+3));
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
		uint8_t y = random8(max(3, numLeds/4));
		heatMap[y] = qadd8(heatMap[y], random8(160, 255));
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
