/* 
* ColorsLedEffect.h
*
*/


#ifndef __COLORSLEDEFFECT_H__
#define __COLORSLEDEFFECT_H__

#include "ILedEffect.h"

class ColorsLedEffect : public ILedEffect
{
private:
	uint8_t hue = 0;
	
public:
	ColorsLedEffect(CRGB leds[], uint16_t count);
	~ColorsLedEffect();
	virtual void refresh() override;

private:
	ColorsLedEffect( const ColorsLedEffect &c );
	ColorsLedEffect& operator=( const ColorsLedEffect &c );

};

#endif //__COLORSLEDEFFECT_H__
