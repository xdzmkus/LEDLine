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
	BugsLedEffect(CRGB leds[], uint16_t count, uint8_t bugs = 0);
	~BugsLedEffect();
	virtual void refresh() override;

private:
	BugsLedEffect( const BugsLedEffect &c );
	BugsLedEffect& operator=( const BugsLedEffect &c );

};

#endif //__BUGSLEDEFFECT_H__
