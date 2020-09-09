/* 
* BugsLedEffect.h
*
*/

#ifndef __BUGSLEDEFFECT_H__
#define __BUGSLEDEFFECT_H__

#include "ILedEffect.h"

class BugsLedEffect : public ILedEffect
{
private:
	const uint8_t BUGS_MAX_SPEED = 20;

	CRGB*		bugColors;
	int8_t*		bugSpeed;
	uint16_t*	bugPosition;
	uint8_t		numBugs;

public:
	BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugs = 0);
	~BugsLedEffect();
	
	void reset() override;
	bool paint() override;

private:
	BugsLedEffect(const BugsLedEffect&);
	BugsLedEffect& operator=(const BugsLedEffect&);

};

#endif //__BUGSLEDEFFECT_H__
