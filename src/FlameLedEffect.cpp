/*
* FlameLedEffect.cpp
*
*/

#include "FlameLedEffect.h"

const char* const FlameLedEffect::name = "FLAME";

FlameLedEffect::FlameLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, bool reversed)
	: LedEffect(leds, count, Hz), fireReversed(reversed), gPal(HeatColors_p)
{
	init();

	heatMap = new uint8_t[count];
}

FlameLedEffect::~FlameLedEffect()
{
	delete[] heatMap;
}

void FlameLedEffect::init()
{
	LedEffect::init();
}

bool FlameLedEffect::paint()
{
	if (!LedEffect::isReady())
		return false;

	// SPARKING: What chance (out of 255) is there that a new spark will be lit?
	// Higher chance = more roaring fire.  Lower chance = more flickery fire.
	// Default 120, suggested range 50-200.
	const uint8_t SPARKING = 120;

	random16_add_entropy(random16());

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
	if (random8() < SPARKING)
	{
		uint8_t y = random8(numLeds>>2);
		heatMap[y] = qadd8(heatMap[y], random8(160, 255));
	}

	// Step 4.  Map from heatMap cells to LED colors
	for (uint16_t j = 0; j < numLeds; j++)
	{
		// Scale the heatMap value from 0-255 down to 0-240
		// for best results with color palettes.
		uint8_t colorindex = scale8(heatMap[j], 240);
		CRGB color = ColorFromPalette(gPal, colorindex);
		uint16_t pixelnumber = fireReversed ? (numLeds - 1) - j : j;
		ledLine[pixelnumber] = color;
	}

	return true;
}
