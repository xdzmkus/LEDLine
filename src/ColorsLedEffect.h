/* 
* ColorsLedEffect.h
*
*/

#ifndef __COLORSLEDEFFECT_H__
#define __COLORSLEDEFFECT_H__

#include "ILedEffect.h"

class ColorsLedEffect : public ILedEffect
{
public:

	static const char* const name;

protected:

	uint8_t hue;
	
public:
	ColorsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz);
	~ColorsLedEffect();

	void reset() override;
	bool paint() override;

	operator const char* () const { return name; }

private:
	ColorsLedEffect(const ColorsLedEffect&) = delete;
	ColorsLedEffect& operator=(const ColorsLedEffect&) = delete;

};

#endif //__COLORSLEDEFFECT_H__
