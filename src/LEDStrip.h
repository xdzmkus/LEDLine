// LEDStrip.h

#ifndef _LEDSTRIP_h
#define _LEDSTRIP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <GyverTimer.h>
#include <FastLED.h>
#include "ILedEffect.h"

class LEDStrip
{
protected:

	CRGB*		leds;
	uint16_t	numLeds;

	ILedEffect* effect = NULL;

	GTimer_ms effectTimer;

	enum LED_STATE
	{
		OFF,
		ON,
		BUGS,
		GLOWWORM,
		COLORS,
		RAINBOW,
		SPARKLES,
		FLAME,
		FLASHES
	} stripState = OFF;

public:

	LEDStrip(CRGB leds[], uint16_t numLeds);
	~LEDStrip();

	virtual void save(int memIdx);
	virtual void load(int memIdx);

	virtual void nextMode();

	virtual bool isUpdated();

	virtual void turnON();
	virtual void turnOFF();
	virtual void turnBugs();
	virtual void turnGlowworm();
	virtual void turnColors();
	virtual void turnRainbow();
	virtual void turnSparkles();
	virtual void turnFlame();
	virtual void turnFlashes();
};

#endif
