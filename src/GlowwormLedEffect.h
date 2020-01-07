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
	boolean direction = true;
	
public:
	GlowwormLedEffect(CRGB leds[], uint16_t count, CRGB color = CRGB::White);
	~GlowwormLedEffect();

	virtual void refresh() override;

private:
	GlowwormLedEffect( const GlowwormLedEffect &c );
	GlowwormLedEffect& operator=( const GlowwormLedEffect &c );

};

#endif //__GLOWWORMLEDEFFECT_H__
