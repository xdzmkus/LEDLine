/*
* ILedLine.hpp
*
*/

#ifndef _ILEDLINE_HPP_
#define _ILEDLINE_HPP_

#include <FastLED.h>

template <CRGB* const ledLine, const uint16_t numLeds>
class ILedLine
{
public:

	ILedLine()
	{
	};

	virtual ~ILedLine()
	{
	};

	CRGB& operator[](uint16_t index)
	{
		return ledLine[index];
	};

	void fillAllLeds(CRGB color)
	{
		for (uint16_t i = 0; i < numLeds; i++)
		{
			ledLine[i] = color;
		}
	};

	void clearAllLeds()
	{
		// zero out the led data managed by this effect
		memset8((void*)ledLine, 0, sizeof(struct CRGB) * numLeds);
	};

	static CRGB getRandomColor()
	{
		return CHSV(random(0, 255), 255, 255);
	};

private:

	ILedLine(const ILedLine&) = delete;
	ILedLine& operator=(const ILedLine&) = delete;

};

#endif
