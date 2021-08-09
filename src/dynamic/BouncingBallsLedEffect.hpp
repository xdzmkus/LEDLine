/* 
* BouncingBallsLedEffect.hpp
*
*/

#ifndef __BOUNSINGBALLSLEDEFFECT_HPP__
#define __BOUNSINGBALLSLEDEFFECT_HPP__

#include "ILedLine.hpp"
#include "ILedEffect.hpp"

template <CRGB* const ledLine, const uint16_t numLeds>
class BouncingBallsLedEffect : public ILedLine<ledLine, numLeds>, public ILedEffect
{

public:

	static const char* const name;

private:

	const float Gravity = 9.8;
	const float MaxVelocity;

	struct BOUNCING
	{
		CRGB	 color;
		uint16_t position;
		float	 height;
		float	 velocity;
		uint8_t	 dampingPercentage;
		unsigned long startTime;
	}
	*balls = nullptr;

	const uint8_t numBalls;

public:

	BouncingBallsLedEffect(uint16_t Hz, uint8_t ballsCount = 0);
	~BouncingBallsLedEffect();
	
	void reset() override;
	void paint() override;

	operator const char* () const {	return name; }

	const uint8_t getNumBalls() const { return numBalls; };

private:

	BouncingBallsLedEffect(const BouncingBallsLedEffect&) = delete;
	BouncingBallsLedEffect& operator=(const BouncingBallsLedEffect&) = delete;

};

template <CRGB* const ledLine, const uint16_t numLeds>
const char* const BouncingBallsLedEffect<ledLine, numLeds>::name = "BOUNCINGBALLS";

template <CRGB* const ledLine, const uint16_t numLeds>
BouncingBallsLedEffect<ledLine, numLeds>::BouncingBallsLedEffect(uint16_t Hz, uint8_t ballsCount)
	: ILedEffect(Hz), MaxVelocity(sqrt(2 * Gravity * (numLeds - 1))), numBalls((ballsCount == 0 || ballsCount >= numLeds) ? random(1, constrain(numLeds, 1, 255)) : ballsCount)
{
	balls = new BOUNCING[numBalls];

	reset();
}

template <CRGB* const ledLine, const uint16_t numLeds>
BouncingBallsLedEffect<ledLine, numLeds>::~BouncingBallsLedEffect()
{
	if (balls != nullptr)
	{
		delete[] balls;
		balls = nullptr;
	}
}

template <CRGB* const ledLine, const uint16_t numLeds>
void BouncingBallsLedEffect<ledLine, numLeds>::reset()
{
	ILedEffect::reset();

	if (balls != nullptr)
	{
		for (uint8_t i = 0; i < numBalls; i++)
		{
			balls[i].color = ILedLine<ledLine, numLeds>::getRandomColor();
			balls[i].startTime = getClock();
			balls[i].height = 0;
			balls[i].position = 0;
			balls[i].velocity = MaxVelocity;
			balls[i].dampingPercentage = random8(70, 90);
		}
	}

	ILedLine<ledLine, numLeds>::clearAllLeds();
}

template <CRGB* const ledLine, const uint16_t numLeds>
void BouncingBallsLedEffect<ledLine, numLeds>::paint()
{
	if (balls == nullptr) return;

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
				balls[i].dampingPercentage = random8(70, 90);
			}
		}

		ledLine[balls[i].position] = CRGB::Black;
		balls[i].position = round(balls[i].height);
		ledLine[balls[i].position] = balls[i].color;
	}
}

#endif

