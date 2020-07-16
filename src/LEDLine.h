// LEDLine.h

#ifndef _LEDLINE_h
#define _LEDLINE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <GyverTimer.h>
#include <FastLED.h>
#include "ILedEffect.h"

class LEDLine
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
		FLASHES,
		FLAG
	} lineState = OFF;

public:

	LEDLine(CRGB leds[], uint16_t numLeds, uint16_t refreshInterval = 80);
	~LEDLine();

	virtual void saveState(int memIdx);
	virtual void loadState(int memIdx);
	virtual void nextState();

	virtual bool refresh();

	virtual void turnON();
	virtual void turnOFF();
	virtual void turnBugs();
	virtual void turnGlowworm();
	virtual void turnColors();
	virtual void turnRainbow();
	virtual void turnSparkles();
	virtual void turnFlame();
	virtual void turnFlashes();
	virtual void turnFlag();
	
};

#endif
