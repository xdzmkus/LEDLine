#include "FlagLedEffect.h"

FlagLedEffect::FlagLedEffect(CRGB leds[], uint16_t count, uint16_t Hz, FLAG flag, uint8_t step)
	: ILedEffect(leds, count, Hz), flag(flag), step_count(step), step_direction(true)
{
	step_position = step_count != 0 ? flag.count1 : 0;
}

FlagLedEffect::~FlagLedEffect()
{
}

void FlagLedEffect::reset()
{
	ILedEffect::reset();
	step_position = step_count != 0 ? flag.count1 : 0;
	step_direction = true;
}

bool FlagLedEffect::paint()
{
	if (!ILedEffect::paint())
		return false;

	uint16_t position = 0;

	if (flag.count1 == 0 || flag.count2 == 0 || flag.count3 == 0) return;

	if (step_count == 0)
	{
		// zigzag flag
		while (position < numLeds)
		{
			for (uint16_t firstColorCount = 0; firstColorCount < (flag.count1 + step_line[step_position]) && position < numLeds; firstColorCount++)
				ledLine[position++] = flag.rgb1;
			for (uint16_t secondColorCount = 0; secondColorCount < flag.count2 && position < numLeds; secondColorCount++)
				ledLine[position++] = flag.rgb2;
			for (uint16_t thirdColorCount = 0; thirdColorCount < (flag.count3 - step_line[step_position]) && position < numLeds; thirdColorCount++)
				ledLine[position++] = flag.rgb3;

			if (++step_position >= STEP_WIDE) step_position = 0;
		}
	}
	else
	{
		// linear flag
		if (step_direction)
		{
			step_position += step_count;
			if (step_position >= flag.count1 + flag.count2 / 4)
			{
				step_direction = false;
			}
		}
		else
		{
			step_position -= step_count;
			if (step_position <= flag.count1 - flag.count2 / 4)
			{
				step_direction = true;
			}
		}

		for (uint16_t firstColorCount = 0; firstColorCount < step_position && position < numLeds; firstColorCount++)
			ledLine[position++] = flag.rgb1;
		for (uint16_t secondColorCount = step_position; secondColorCount < (step_position + flag.count2) && position < numLeds; secondColorCount++)
			ledLine[position++] = flag.rgb2;
		for (uint16_t thirdColorCount = 0; thirdColorCount < flag.count3 - (step_position - flag.count1) && position < numLeds; thirdColorCount++)
			ledLine[position++] = flag.rgb3;
	}

	return true;
}
