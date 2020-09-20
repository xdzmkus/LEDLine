
#if defined(ESP32) || defined(ESP8266)
#define LED_PIN 13  // leds pin
#define BTN_PIN 0   // button pin
#else
#define LED_PIN 9   // leds pin
#define BTN_PIN 10  // button pin
#endif

//#define TOUCH_BUTTON
#include <GyverButton.h>
#if defined(TOUCH_BUTTON)
GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);
#else
GButton touch(BTN_PIN, HIGH_PULL, NORM_OPEN);
#endif

#define NUM_LEDS 256
#define CURRENT_LIMIT 8000

#define MAX_BRIGHTNESS 300
#define MIN_BRIGHTNESS 30

#define EEPROM_ADDRESS_EFFECT 0

#include <FastLED.h>
#include "LEDLine.h"
#include "FlashLedEffect.h"
#include "GlowwormLedEffect.h"
#include "ColorsLedEffect.h"
#include "RainbowLedEffect.h"
#include "SparklesLedEffect.h"
#include "BugsLedEffect.h"
#include "FlameLedEffect.h"
#include "FlagLedEffect.h"

CRGB leds[NUM_LEDS];

#define NUM_EFFECTS 8
ILedEffect* effects[NUM_EFFECTS] =
{
	new BugsLedEffect(leds, NUM_LEDS, 20),
	new GlowwormLedEffect(leds, NUM_LEDS, 30),
	new ColorsLedEffect(leds, NUM_LEDS, 10),
	new RainbowLedEffect(leds, NUM_LEDS, 10),
	new SparklesLedEffect(leds, NUM_LEDS, 10),
	new FlameLedEffect(leds, NUM_LEDS, 10),
	new FlashLedEffect(leds, NUM_LEDS, 1, CRGB::Yellow),
	new FlagLedEffect(leds, NUM_LEDS, 30, { CRGB::White, 80, CRGB::Red, 96, CRGB::White, 80 }, 3)
};

LEDLine ledLine(effects, NUM_EFFECTS);

uint16_t brightness = MIN_BRIGHTNESS;

void setup()
{
	randomSeed(analogRead(0));

	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(brightness);
	FastLED.clear(true);

	ledLine.loadState(EEPROM_ADDRESS_EFFECT);
	ledLine.resume();

	touch.setTimeout(300);
	touch.setStepTimeout(50);

	Serial.begin(115200);
	Serial.println(F("LEDLine"));
}

void loop()
{
	touch.tick();

	if (touch.hasClicks())
	{
		switch (touch.getClicks())
		{
		case 1:
			ledLine.resume();
			ledLine.nextState();
			FastLED.show();
			break;
		case 2:
			ledLine.pause();
			FastLED.clear(true);
			break;
		case 3:
			ledLine.pause();
			ledLine.saveState(EEPROM_ADDRESS_EFFECT);
			break;
		default:
			break;
		}
	}
	if (touch.isStep())
	{
		brightness -= 5;

		if (brightness > MAX_BRIGHTNESS)
			brightness = MAX_BRIGHTNESS;

		FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, 255));
		FastLED.show();
	}

	if (ledLine.isChanged())
	{
		FastLED.show();
	}
}
