#include "LEDLine.h"

LEDLine::LEDLine()
{
}

LEDLine::~LEDLine()
{
}

bool LEDLine::setEffectByIdx(uint8_t idx)
{
	if (idx >= howManyEffects()) return false;

	return setEffectByName(getAllEffectsNames()[idx]);
}

bool LEDLine::setNextEffect()
{
	uint8_t nextEffectIdx = getEffectIdx() + 1;

	if (nextEffectIdx >= howManyEffects())	nextEffectIdx = 0;

	return setEffectByIdx(nextEffectIdx);
}

const char* LEDLine::getEffectName() const
{
	return (effect != nullptr) ? static_cast<const char*>(*effect) : nullptr;
}

uint8_t LEDLine::getEffectIdx() const
{
	const char* effectName = getEffectName();

	if (effectName != nullptr)
	{
		for (uint8_t idx = 0; idx < howManyEffects(); idx++)
		{
			if (strcmp(getAllEffectsNames()[idx], effectName) == 0)	return idx;
		}
	}

	return howManyEffects();	// non-existing effect index
}

void LEDLine::turnOn()
{
	if (effect == nullptr) setEffectByIdx(0);

	if (effect != nullptr) effect->start();
}

void LEDLine::turnOff()
{
	if (effect != nullptr) effect->stop();
}

bool LEDLine::isOn() const
{
	return (effect != nullptr) ? effect->isActive() : false;
}

bool LEDLine::refresh()
{
	if (effect == nullptr || !effect->isReady()) return false;

	effect->paint();

	return true;
}

const char* LEDLine::getState() const
{
	const char* currentEffect = getEffectName();

	return (!isOn() || currentEffect == nullptr) ? OFF : currentEffect;
};
