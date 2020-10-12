/* 
* GlowwormLedEffect.h
*
*/

#ifndef __GLOWWORMLEDEFFECT_H__
#define __GLOWWORMLEDEFFECT_H__

#include "LedEffect.h"

class GlowwormLedEffect : public LedEffect
{
public:

	static const char* const name;

protected:

	CRGB rgb;
	uint16_t position = 0;
	bool direction = true;
	
public:
	GlowwormLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color = CRGB::White);
	~GlowwormLedEffect();

	void reset() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	GlowwormLedEffect(const GlowwormLedEffect&);
	GlowwormLedEffect& operator=(const GlowwormLedEffect&);

};

#endif //__GLOWWORMLEDEFFECT_H__
