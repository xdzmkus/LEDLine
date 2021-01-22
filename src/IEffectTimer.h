#ifndef _IEFFECT_TIMER_H
#define _IEFFECT_TIMER_H

class IEffectTimer
{
protected:

	bool active;
	unsigned long interval;
	unsigned long lastTime;

public:

	IEffectTimer(unsigned long interval, bool start = true)
		: active(start), interval(interval), lastTime(0)
	{
	};

	virtual ~IEffectTimer()
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

class MillisTimer : public IEffectTimer
{
public:

	static const unsigned long CLOCKS_IN_SEC = 1000UL;

	MillisTimer(unsigned long interval, bool start = true)
		: IEffectTimer(interval, start)
	{
	};

protected:
	unsigned long getClock() const override
	{
		return millis();
	};
};

class MicrosTimer : public IEffectTimer
{
public:

	static const unsigned long CLOCKS_IN_SEC = 1000000UL;

	MicrosTimer(unsigned long interval, bool start = true)
		: IEffectTimer(interval, start)
	{
	};

protected:
	unsigned long getClock() const override
	{
		return micros();
	};
};


#endif
