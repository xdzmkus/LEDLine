#include "LEDLine.h"

#include <EEPROM.h>


LEDLine::LEDLine(ILedEffect* effects[], uint8_t numEffects)
	: effects(effects), numEffects(numEffects)
{
}

LEDLine::~LEDLine()
{
}

void LEDLine::saveState(int memIdx)
{
#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(1);
	EEPROM.write(memIdx, currentEffect);
	EEPROM.commit();
#else
	EEPROM.update(memIdx, currentEffect);
#endif
}

void LEDLine::loadState(int memIdx)
{
#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(1);
#endif

	currentEffect = EEPROM.read(memIdx);

	if (currentEffect >= numEffects)
		currentEffect = 0;

	if (effects != NULL && effects[currentEffect] != NULL && numEffects != 0)
	{
		effects[currentEffect]->reset();
	}
}

void LEDLine::nextState()
{
	if (++currentEffect >= numEffects)
		currentEffect = 0;

	if (effects != NULL && effects[currentEffect] != NULL && numEffects != 0)
	{
		effects[currentEffect]->reset();
	}
}

void LEDLine::pause()
{
	isOn = false;
}

void LEDLine::resume()
{
	isOn = true;
}

bool LEDLine::isChanged()
{
	if (!isOn || effects == NULL || effects[currentEffect] == NULL || numEffects == 0)
		return false;

	return effects[currentEffect]->paint();
}
