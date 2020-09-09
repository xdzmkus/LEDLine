/* 
* GlowwormLedEffect.h
*
*/

#ifndef __GLOWWORMLEDEFFECT_H__
#define __GLOWWORMLEDEFFECT_H__

#include "ILedEffect.h"

class GlowwormLedEffect : public ILedEffect
{
private:
	CRGB rgb;
	uint16_t position = 0;
	bool direction = true;
	
public:
	GlowwormLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, CRGB color = CRGB::White);
	~GlowwormLedEffect();

	void reset() override;
	bool paint() override;

private:
	GlowwormLedEffect(const GlowwormLedEffect&);
	GlowwormLedEffect& operator=(const GlowwormLedEffect&);

};

#endif //__GLOWWORMLEDEFFECT_H__
