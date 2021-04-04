/* 
* BugsLedEffect.h
*
*/

#ifndef __BUGSLEDEFFECT_H__
#define __BUGSLEDEFFECT_H__

#include "ILedEffect.h"

class BugsLedEffect : public ILedLine, public ILedEffect
{
public:

	static const char* const name;

protected:

	const uint8_t BUGS_MAX_SPEED = 20;

	const uint8_t numBugs;

	struct BUGS
	{
		CRGB color;
		int8_t speed;
		uint16_t position;
	}
	*bugs = nullptr;

public:
	BugsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t bugs = 1);
	~BugsLedEffect();
	
	void reset() override;
	void paint() override;

	operator const char* () const {	return name; }

private:
	BugsLedEffect(const BugsLedEffect&) = delete;
	BugsLedEffect& operator=(const BugsLedEffect&) = delete;

};

#endif //__BUGSLEDEFFECT_H__
