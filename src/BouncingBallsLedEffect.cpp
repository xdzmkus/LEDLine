/*
* BouncingBallsLedEffect.cpp
*
*/

#include "BouncingBallsLedEffect.h"

const char* const BouncingBallsLedEffect::name = "BOUNCINGBALLS";

BouncingBallsLedEffect::BouncingBallsLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, uint8_t ballsCount)
	: ILedEffect(leds, count, Hz), MaxVelocity(sqrt(2 * Gravity * (count - 1))), numBalls(ballsCount)
{
	if (numBalls > 0)
	{
		balls = new BOUNCING[numBalls];
	}

	init();
}

BouncingBallsLedEffect::~BouncingBallsLedEffect()
{
	if (balls != nullptr)
	{
		delete[] balls;
		balls = nullptr;
	}
}

void BouncingBallsLedEffect::init()
{
	if (balls != nullptr)
	{
		for (uint8_t i = 0; i < numBalls; i++)
		{
			balls[i].color = getRandomColor();
			balls[i].startTime = getClock();
			balls[i].height = 0;
			balls[i].position = 0;
			balls[i].velocity = MaxVelocity;
			balls[i].dampingPercentage = random(70, 90);
		}
	}

	clearAllLeds();
}

bool BouncingBallsLedEffect::paint()
{
	if (!isReady() || balls == nullptr)
		return false;

	for (uint8_t i = 0; i < numBalls; i++)
	{
		float timeOfFlying = static_cast<float>(getClock() - balls[i].startTime) / ILedEffect::CLOCKS_IN_SEC;
		balls[i].height = balls[i].velocity * timeOfFlying - 0.5 * Gravity * timeOfFlying * timeOfFlying;

		if (balls[i].height < 0)
		{
			balls[i].height = 0;
			balls[i].velocity *= balls[i].dampingPercentage / 100.0;
			balls[i].startTime = getClock();

			if (balls[i].velocity < 0.01)
			{
				balls[i].velocity = MaxVelocity;
				balls[i].dampingPercentage = random(70, 90);
			}
		}

		ledLine[balls[i].position] = CRGB::Black;
		balls[i].position = round(balls[i].height);
		ledLine[balls[i].position] = balls[i].color;
	}

	return true;
}
