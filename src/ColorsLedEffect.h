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
	uint8_t hue;
	
public:
	ColorsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz);
	~ColorsLedEffect();

	void reset() override;
	bool paint() override;

private:
	ColorsLedEffect(const ColorsLedEffect&);
	ColorsLedEffect& operator=(const ColorsLedEffect&);

};

#endif //__COLORSLEDEFFECT_H__
