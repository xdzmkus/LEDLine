/* 
* FlashLedEffect.h
*
*/


#ifndef __FLASHLEDEFFECT_H__
#define __FLASHLEDEFFECT_H__

#include "ILedEffect.h"

class FlashLedEffect : public ILedEffect
{
private:
	CRGB		flashColor;
	uint16_t	flashDelay;
	uint16_t	flashCount = -1;
	uint32_t	flashTime = 0;
	bool		flashState = false;
	
//functions
public:
	FlashLedEffect(CRGB leds[], uint16_t count, CRGB color, uint16_t delay, uint16_t times = -1);
	~FlashLedEffect();
	virtual void refresh() override;

private:
	FlashLedEffect( const FlashLedEffect &c );
	FlashLedEffect& operator=( const FlashLedEffect &c );

};

#endif //__FLASHLEDEFFECT_H__
