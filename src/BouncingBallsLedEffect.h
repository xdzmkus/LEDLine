/* 
* BouncingBallsLedEffect.h
*
*/

#ifndef __BOUNSINGBALLSLEDEFFECT_H__
#define __BOUNSINGBALLSLEDEFFECT_H__

#include "LedEffect.h"

class BouncingBallsLedEffect : public LedEffect
{
private:

	const float Gravity = -9.81;
	const int StartHeight = 1;
	const float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);

public:

	static const char* const name;

protected:

	struct BOUNCING
	{
		CRGB  color;
		int   position;
		float height;
		float impactVelocity;
		float timeSinceLastBounce;
		long  clockTimeSinceLastBounce;
		float dampening;
	}
	*balls;

	uint8_t	numBalls;

public:
	BouncingBallsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t ballsCount = 0);
	~BouncingBallsLedEffect();
	
	void init() override;
	bool paint() override;

	operator const char* () const {	return name; }

private:
	BouncingBallsLedEffect(const BouncingBallsLedEffect&) = delete;
	BouncingBallsLedEffect& operator=(const BouncingBallsLedEffect&) = delete;

};

#endif

