/* 
* SparklesLedEffect.h
*
*/

#ifndef __SPARKLESLEDEFFECT_H__
#define __SPARKLESLEDEFFECT_H__

#include "ILedEffect.h"

class SparklesLedEffect : public ILedLine, public ILedEffect
{
public:

	static const char* const name;

protected:

	const uint8_t SPARKLES_TRACK_STEP = 20;

	const CRGB color;

public:
	SparklesLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color = CRGB::Black);
	~SparklesLedEffect();

	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:
	SparklesLedEffect(const SparklesLedEffect&) = delete;
	SparklesLedEffect& operator=(const SparklesLedEffect&) = delete;
};

#endif //__SPARKLESLEDEFFECT_H__
