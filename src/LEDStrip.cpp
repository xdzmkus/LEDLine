#include "LEDStrip.h"

#include "ConstLedEffect.h"
#include "FlashLedEffect.h"
#include "GlowwormLedEffect.h"
#include "ColorsLedEffect.h"
#include "RainbowLedEffect.h"
#include "SparklesLedEffect.h"
#include "BugsLedEffect.h"
#include "FlameLedEffect.h"

#include <EEPROM.h>


LEDStrip::LEDStrip(CRGB leds[], uint16_t numLeds)
	: leds(leds), numLeds(numLeds)
{
	effectTimer.setInterval(80);
	effectTimer.start();
}

LEDStrip::~LEDStrip()
{
	if (effect != NULL)
	{
		delete effect;
	}
}

void LEDStrip::save(int memIdx)
{
#if defined(ESP32) || defined(ESP8266)
	EEPROM.write(memIdx, static_cast<uint8_t>(stripState));
	EEPROM.commit();
#else
	EEPROM.update(memIdx, static_cast<uint8_t>(stripState));
#endif
}

void LEDStrip::load(int memIdx)
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
	case ON:
		turnON();
		break;
	default:
		turnOFF();
		break;
	}

	effectTimer.reset();
}

void LEDStrip::nextMode()
{
	switch (stripState)
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
	default:
		turnBugs();
		break;
	}

	effectTimer.reset();
}

bool LEDStrip::isUpdated()
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

void LEDStrip::turnON()
{
	stripState = ON;
	if (effect != NULL) delete effect;
	effect = new ConstLedEffect(leds, numLeds, CRGB::White);
}

void LEDStrip::turnOFF()
{
	stripState = OFF;
	if (effect != NULL) delete effect;
	effect = new ConstLedEffect(leds, numLeds, CRGB::Black);
}

void LEDStrip::turnBugs()
{
	stripState = BUGS;
	if (effect != NULL) delete effect;
	effect = new BugsLedEffect(leds, numLeds);
}

void LEDStrip::turnGlowworm()
{
	stripState = GLOWWORM;
	if (effect != NULL) delete effect;
	effect = new GlowwormLedEffect(leds, numLeds);
}

void LEDStrip::turnColors()
{
	stripState = COLORS;
	if (effect != NULL) delete effect;
	effect = new ColorsLedEffect(leds, numLeds);
}

void LEDStrip::turnRainbow()
{
	stripState = RAINBOW;
	if (effect != NULL) delete effect;
	effect = new RainbowLedEffect(leds, numLeds);
}

void LEDStrip::turnSparkles()
{
	stripState = SPARKLES;
	if (effect != NULL) delete effect;
	effect = new SparklesLedEffect(leds, numLeds);
}

void LEDStrip::turnFlame()
{
	stripState = FLAME;
	if (effect != NULL) delete effect;
	effect = new FlameLedEffect(leds, numLeds);
}

void LEDStrip::turnFlashes()
{
	stripState = FLASHES;
	if (effect != NULL) delete effect;
	effect = new FlashLedEffect(leds, numLeds, CRGB::Red, 700);
}
