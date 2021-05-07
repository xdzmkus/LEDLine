#if defined(ESP8266)
#define LED_PIN D1  // D1 leds pin (connected to D5 on my NodeMCU1.0 !!!)
#else
#define LED_PIN 9   // leds pin
#endif

#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

#include <FastLED.h>
#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20

uint16_t brightness = MAX_BRIGHTNESS / 2;

CRGB leds[NUM_LEDS];

#include "LEDLine.h"

LEDLine ledLine(leds, NUM_LEDS);

#include "EffectTimer.h"

#define EFFECT_DURATION_SEC 60
MillisTimer timerEffects(EFFECT_DURATION_SEC * MillisTimer::CLOCKS_IN_SEC);


void changeEffect()
{
	ledLine.setNextEffect();

	Serial.print(F("EFFECT: "));
	Serial.println(ledLine.getEffectName());
}

void setupLED()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
	FastLED.clear(true);
}

void setup()
{
	randomSeed(analogRead(UNPINNED_ANALOG_PIN));

	Serial.begin(115200);

	Serial.println(F("LEDLine EFFECTS:"));
	for (uint8_t var = 0; var < ledLine.getAllEffectsNumber(); var++)
	{
		Serial.println(ledLine.getAllEffectsNames()[var]);
	}

	setupLED();

	ledLine.turnOn();

	Serial.print(F("EFFECT: "));
	Serial.println(ledLine.getEffectName());

	timerEffects.start();
}

void loop()
{
	if (timerEffects.isReady())
		changeEffect();

	if (ledLine.refresh())
	{
		FastLED.show();
	}
}
