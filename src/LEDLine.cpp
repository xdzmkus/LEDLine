#include "LEDLine.h"

#include "ConstLedEffect.h"
#include "FlashLedEffect.h"
#include "GlowwormLedEffect.h"
#include "ColorsLedEffect.h"
#include "RainbowLedEffect.h"
#include "SparklesLedEffect.h"
#include "BugsLedEffect.h"
#include "FlameLedEffect.h"
#include "FlagLedEffect.h"

#include <EEPROM.h>


LEDLine::LEDLine(CRGB leds[], uint16_t numLeds, uint16_t refreshInterval)
	: leds(leds), numLeds(numLeds)
{
	effectTimer.setInterval(refreshInterval);
	effectTimer.start();
}

LEDLine::~LEDLine()
{
	if (effect != NULL)
	{
		delete effect;
	}
}

void LEDLine::saveState(int memIdx)
{
#if defined(ESP32) || defined(ESP8266)
	EEPROM.write(memIdx, static_cast<uint8_t>(lineState));
	EEPROM.commit();
#else
	EEPROM.update(memIdx, static_cast<uint8_t>(lineState));
#endif
}

void LEDLine::loadState(int memIdx)
{
	switch (static_cast<LED_STATE>(EEPROM.read(memIdx)))
	{
	case BUGS:
		turnBugs();
		break;
	case GLOWWORM:
		turnGlowworm();
		break;
	case COLORS:
		turnColors();
		break;
	case RAINBOW:
		turnRainbow();
		break;
	case SPARKLES:
		turnSparkles();
		break;
	case FLAME:
		turnFlame();
		break;
	case FLASHES:
		turnFlashes();
		break;
	case FLAG:
		turnFlag();
		break;
	case ON:
		turnON();
		break;
	default:
		turnOFF();
		break;
	}

	effectTimer.reset();
}

void LEDLine::nextState()
{
	switch (lineState)
	{
	case BUGS:
		turnGlowworm();
		break;
	case GLOWWORM:
		turnColors();
		break;
	case COLORS:
		turnRainbow();
		break;
	case RAINBOW:
		turnSparkles();
		break;
	case SPARKLES:
		turnFlame();
		break;
	case FLAME:
		turnFlashes();
		break;
	case FLASHES:
		turnFlag();
		break;
	case FLAG:
	default:
		turnBugs();
		break;
	}

	effectTimer.reset();
}

bool LEDLine::refresh()
{
	if (effect == NULL)
		return false;

	if (effectTimer.isReady())
	{
		effect->refresh();
		return true;
	}

	return false;
}

void LEDLine::turnON()
{
	lineState = ON;
	if (effect != NULL) delete effect;
	effect = new ConstLedEffect(leds, numLeds, CRGB::White);
}

void LEDLine::turnOFF()
{
	lineState = OFF;
	if (effect != NULL) delete effect;
	effect = new ConstLedEffect(leds, numLeds, CRGB::Black);
}

void LEDLine::turnBugs()
{
	lineState = BUGS;
	if (effect != NULL) delete effect;
	effect = new BugsLedEffect(leds, numLeds);
}

void LEDLine::turnGlowworm()
{
	lineState = GLOWWORM;
	if (effect != NULL) delete effect;
	effect = new GlowwormLedEffect(leds, numLeds);
}

void LEDLine::turnColors()
{
	lineState = COLORS;
	if (effect != NULL) delete effect;
	effect = new ColorsLedEffect(leds, numLeds);
}

void LEDLine::turnRainbow()
{
	lineState = RAINBOW;
	if (effect != NULL) delete effect;
	effect = new RainbowLedEffect(leds, numLeds);
}

void LEDLine::turnSparkles()
{
	lineState = SPARKLES;
	if (effect != NULL) delete effect;
	effect = new SparklesLedEffect(leds, numLeds);
}

void LEDLine::turnFlame()
{
	lineState = FLAME;
	if (effect != NULL) delete effect;
	effect = new FlameLedEffect(leds, numLeds);
}

void LEDLine::turnFlashes()
{
	lineState = FLASHES;
	if (effect != NULL) delete effect;
	effect = new FlashLedEffect(leds, numLeds, CRGB::Red, 700);
}

void LEDLine::turnFlag()
{
	lineState = FLAG;
	if (effect != NULL) delete effect;
	effect = new FlagLedEffect(leds, numLeds);
}
