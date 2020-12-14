#ifndef _EFFECT_TIMER_H
#define _EFFECT_TIMER_H

class EffectTimer
{
protected:

	bool active;
	unsigned long interval;
	unsigned long lastTime;

public:

	EffectTimer(unsigned long interval, bool start = true)
		: active(start), interval(interval), lastTime(0)
	{
	};

	virtual ~EffectTimer()
	{
	};

	virtual void start() { active = true; lastTime = getClock(); };

	virtual void stop() { active = false; };

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
	virtual unsigned long getClock() const = 0;
};

class MillisTimer : public EffectTimer
{
public:

	static const unsigned long CLOCKS_IN_SEC = 1000UL;

	MillisTimer(unsigned long interval, bool start = true)
		: EffectTimer(interval, start)
	{
	};

protected:
	unsigned long getClock() const override
	{
		return millis();
	};
};

class MicrosTimer : public EffectTimer
{
public:

	static const unsigned long CLOCKS_IN_SEC = 1000000UL;

	MicrosTimer(unsigned long interval, bool start = true)
		: EffectTimer(interval, start)
	{
	};

protected:
	unsigned long getClock() const override
	{
		return micros();
	};
};


#endif
