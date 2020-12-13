/* 
* BugsLedEffect.h
*
*/

#ifndef __BUGSLEDEFFECT_H__
#define __BUGSLEDEFFECT_H__

#include "LedEffect.h"

class BugsLedEffect : public LedEffect
{
public:

	static const char* const name;

protected:

	const uint8_t BUGS_MAX_SPEED = 20;

	struct BUGS
	{
		CRGB color;
		int8_t speed;
		uint16_t position;
	}
	*bugs;

	uint8_t		numBugs;

public:
	BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugs = 0);
	~BugsLedEffect();
	
	void init() override;
	bool paint() override;

	operator const char* () const {	return name; }

private:
	BugsLedEffect(const BugsLedEffect&) = delete;
	BugsLedEffect& operator=(const BugsLedEffect&) = delete;

};

#endif //__BUGSLEDEFFECT_H__
