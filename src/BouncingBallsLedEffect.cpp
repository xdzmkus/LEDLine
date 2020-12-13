/*
* BouncingBallsLedEffect.cpp
*
*/

#include "BouncingBallsLedEffect.h"

const char* const BouncingBallsLedEffect::name = "BOUNSINGBALLS";

BouncingBallsLedEffect::BouncingBallsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t ballsCount)
	: LedEffect(leds, count, Hz), numBalls(ballsCount == 0 ? random(1, max(1, count / 5)) : ballsCount)
{
	balls = new BOUNCING[numBalls];

	init();
}

BouncingBallsLedEffect::~BouncingBallsLedEffect()
{
	delete[] balls;
}

void BouncingBallsLedEffect::init()
{
	for (int i = 0; i < numBalls; i++)
	{
		balls[i].color = getRandomColor();
		balls[i].clockTimeSinceLastBounce = getClock();
		balls[i].height = StartHeight;
		balls[i].position = 0;
		balls[i].impactVelocity = ImpactVelocityStart;
		balls[i].timeSinceLastBounce = 0;
		balls[i].dampening = 0.90 - float(i) / pow(numBalls, 2);
	}

	LedEffect::init();
}

bool BouncingBallsLedEffect::paint()
{
	if (isReady())
		return false;


	for (int i = 0; i < numBalls; i++)
	{
		ledLine[balls[i].position] = CRGB::Black;

		balls[i].timeSinceLastBounce = getClock() - balls[i].clockTimeSinceLastBounce;
		balls[i].height = 0.5 * Gravity * pow(balls[i].timeSinceLastBounce / LedEffect::CLOCKS_IN_SEC, 2.0) + balls[i].impactVelocity * balls[i].timeSinceLastBounce / LedEffect::CLOCKS_IN_SEC;

		if (balls[i].height < 0)
		{
			balls[i].height = 0;
			balls[i].impactVelocity *= balls[i].dampening;
			balls[i].clockTimeSinceLastBounce = getClock();

			if (balls[i].impactVelocity < 0.01)
			{
				balls[i].impactVelocity = ImpactVelocityStart;
			}
		}

		balls[i].position = round(balls[i].height * (numLeds - 1) / StartHeight);
	}

	for (int i = 0; i < numBalls; i++)
	{
		ledLine[balls[i].position] = balls[i].color;
	}

	return true;
}
