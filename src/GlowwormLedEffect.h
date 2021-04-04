/* 
* GlowwormLedEffect.h
*
*/

#ifndef __GLOWWORMLEDEFFECT_H__
#define __GLOWWORMLEDEFFECT_H__

#include "ILedEffect.h"

class GlowwormLedEffect : public ILedLine, public ILedEffect
{
public:

	static const char* const name;

protected:

	const CRGB rgb;
	uint16_t position = 0;
	bool direction = true;
	
public:
	GlowwormLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color = CRGB::Black);
	~GlowwormLedEffect();

	void reset() override;
	void paint() override;

	operator const char* () const { return name; }

private:
	GlowwormLedEffect(const GlowwormLedEffect&) = delete;
	GlowwormLedEffect& operator=(const GlowwormLedEffect&) = delete;

};

#endif //__GLOWWORMLEDEFFECT_H__
