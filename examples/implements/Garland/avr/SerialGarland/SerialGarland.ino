#define DYNAMIC_EFFECTS

#define LED_PIN 9   // leds pin
#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

#include <FastLED.h>
#define NUM_LEDS 256
#define CURRENT_LIMIT 8000

uint8_t brightness = 127;

CRGB leds[NUM_LEDS];

#ifdef DYNAMIC_EFFECTS
#include "DynamicLEDLine.hpp"
DynamicLEDLine<leds, NUM_LEDS> ledLine;
#else
#include "StaticLEDLine.hpp"
StaticLEDLine<leds, NUM_LEDS> ledLine;
#endif

#define NAME_EFFECT_LENGTH 15

char EFFECT_NAME[NAME_EFFECT_LENGTH + 1];

bool isNewEffect = false;

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent()
{
	static uint8_t receivedBytes = 0;

	while (Serial.available())
	{
		// get the new byte:
		char recvChar = (char)Serial.read();

		// if the incoming character is a newline, set a flag so the main loop can do something about it:
		if (recvChar == '\r' || recvChar == '\n')
		{
			if (receivedBytes == 0) continue; // ignore empty lines

			EFFECT_NAME[receivedBytes] = '\0';
			receivedBytes = 0;
			isNewEffect = true;
		}
		else
		{
			EFFECT_NAME[receivedBytes++] = recvChar;

			if (receivedBytes == NAME_EFFECT_LENGTH)
				receivedBytes = 0;
		}
	}
}

void setupLED()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(brightness);
	FastLED.clear(true);
}

void setup()
{
	randomSeed(analogRead(UNPINNED_ANALOG_PIN));

	Serial.begin(115200);

	setupLED();

	Serial.println(F("LEDLine EFFECTS:"));
	for (uint8_t var = 0; var < ledLine.howManyEffects(); var++)
	{
		Serial.println(ledLine.getAllEffectsNames()[var]);
	}

	ledLine.turnOn();
}

void loop()
{
	if (isNewEffect)
	{
		isNewEffect = false;

		Serial.print(F("NEW_EFFECT:"));
		Serial.println(EFFECT_NAME);

		if (ledLine.setEffectByName(EFFECT_NAME))
		{
			Serial.println(F("OK"));
		}
		else
		{
			Serial.println(F("NONEXISTING"));
		}
		Serial.flush();
	}

	if (ledLine.refresh())
	{
		FastLED.show();
	}
}