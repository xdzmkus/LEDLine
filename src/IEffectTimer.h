#ifndef _IEFFECT_TIMER_H
#define _IEFFECT_TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

template <class T>
class IEffectTimer
{
protected:

	T interval;
	T lastTime;

	bool active = false;

public:

	IEffectTimer(T interval) : interval(interval)
	{
	};

	virtual ~IEffectTimer()
	{
	};

	virtual void start()
	{
		active = true;
		reset();
	};

	virtual void stop()
	{
		active = false;
	};

	virtual void reset()
	{
		lastTime = getClock();
	};

	virtual bool isActive() const
	{
		return active;
	};

	virtual bool isReady()
	{
		if (active && interval)
		{
			auto ticks = getClock();
			if (ticks - lastTime >= interval)
			{
				lastTime = ticks;
				return true;
			}
		}
		return false;
	};

protected:
	virtual T getClock() const = 0;
};

class MillisTimer : public IEffectTimer<unsigned long>
{
public:

	static const unsigned long CLOCKS_IN_SEC = 1000UL;

	MillisTimer(unsigned long interval) : IEffectTimer(interval)
	{
	};

protected:
	unsigned long getClock() const override
	{
		return millis();
	};
};

class MicrosTimer : public IEffectTimer<unsigned long>
{
public:

	static const unsigned long CLOCKS_IN_SEC = 1000000UL;

	MicrosTimer(unsigned long interval)	: IEffectTimer(interval)
	{
	};

protected:
	unsigned long getClock() const override
	{
		return micros();
	};
};


#endif
