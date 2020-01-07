/* 
* SparklesLedEffect.h
*
*/


#ifndef __SPARKLESLEDEFFECT_H__
#define __SPARKLESLEDEFFECT_H__

#include "ILedEffect.h"

class SparklesLedEffect : public ILedEffect
{
private:
	const uint8_t SPARKLES_TRACK_STEP = 40;

public:
	SparklesLedEffect(CRGB leds[], uint16_t count);
	~SparklesLedEffect();
	virtual void refresh() override;

private:
	SparklesLedEffect( const SparklesLedEffect &c );
	SparklesLedEffect& operator=( const SparklesLedEffect &c );

};

#endif //__SPARKLESLEDEFFECT_H__
