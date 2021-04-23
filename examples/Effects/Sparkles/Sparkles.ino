#if defined(ESP8266)
#define LED_PIN D1  // D1 leds pin (connected to D5 on my NodeMCU1.0 !!!)
#else
#define LED_PIN 9   // leds pin
#endif
#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20

uint16_t brightness = MAX_BRIGHTNESS / 2;

#include <FastLED.h>

CRGB leds[NUM_LEDS];

#include "SparklesLedEffect.h"

SparklesLedEffect* effect;

void setupLED()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
	FastLED.clear(true);
}

void setup()
{
	randomSeed(analogRead(UNPINNED_ANALOG_PIN));

	Serial.begin(115200);

	Serial.println(F("Sparkles effect"));

	setupLED();

	effect = new SparklesLedEffect(leds, NUM_LEDS, 10, CRGB::Aquamarine);

	effect->start();
}

void loop()
{
	if (effect->isReady())
	{
		effect->paint();
		FastLED.show();
	}
}