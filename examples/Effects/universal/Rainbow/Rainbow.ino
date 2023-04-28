#if defined(ESP8266)
#define LED_PIN D1  // D1 leds pin (connected to D5 on my NodeMCU1.0 !!!)
#else
#define LED_PIN 9   // leds pin
#endif
#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

#define NUM_LEDS 256
#define RATE_HZ 10
#define CURRENT_LIMIT 8000

uint8_t brightness = 128;

#include <FastLED.h>

CRGB leds[NUM_LEDS];

#include "UniversalLEDLineEffects.h"
RainbowLedEffect<leds, NUM_LEDS> effect(RATE_HZ);

void setupLED()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(brightness);
	FastLED.clear(true);
}

void setup()
{
	randomSeed(analogRead(UNPINNED_ANALOG_PIN));

	Serial.begin(115200);

	Serial.print(F("Effect: "));
	Serial.println(effect.name);

	setupLED();

	effect.start();
}

void loop()
{
	if (effect.isReady())
	{
		effect.paint();
		FastLED.show();
	}
}