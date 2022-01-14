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

LedEffectName LEDLine::getEffectName() const
{
	return (activeEffect != nullptr) ? static_cast<LedEffectName>(*activeEffect) : nullptr;
}

uint8_t LEDLine::getEffectIdx() const
{
	LedEffectName effectName = getEffectName();

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
	if (activeEffect == nullptr) setEffectByIdx(0);

	if (activeEffect != nullptr) activeEffect->start();
}

void LEDLine::turnOff()
{
	if (activeEffect != nullptr) activeEffect->stop();
}

bool LEDLine::isOn() const
{
	return (activeEffect != nullptr) ? activeEffect->isActive() : false;
}

bool LEDLine::refresh()
{
	if (activeEffect == nullptr || !activeEffect->isReady()) return false;

	activeEffect->paint();

	return true;
}

LedState LEDLine::getState() const
{
	LedEffectName currentEffectName = getEffectName();

	return (!isOn() || currentEffectName == nullptr) ? OFF : currentEffectName;
};
