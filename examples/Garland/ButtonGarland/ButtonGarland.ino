#if defined(ESP32) || defined(ESP8266)
#define LED_PIN D3  // D1 leds pin (connected to D5 on my NodeMCU1.0 !!!)
#define BTN_PIN 16  // D0 button pin
#else
#define LED_PIN 9   // leds pin
#define BTN_PIN 10  // button pin
#endif
#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

#include <Denel_Button.h>
Denel_Button btn(BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);

#include <EEPROM.h>
#define EEPROM_ADDRESS_EFFECT 0
#define EEPROM_EFFECT_LENGTH 15

char EFFECT_NAME[EEPROM_EFFECT_LENGTH + 1];

#include <FastLED.h>
#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20

uint16_t brightness = MAX_BRIGHTNESS/2;

CRGB leds[NUM_LEDS];

#include "LEDLine256.h"

LEDLine256 ledLine(leds, NUM_LEDS);

void loadEffect()
{
	Serial.println(F("LEDLine EFFECTS:"));
	for (uint8_t var = 0; var < ledLine.getAllEffectsNumber(); var++)
	{
		Serial.println(ledLine.getAllEffectsNames()[var]);
	}

#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(EEPROM_EFFECT_LENGTH);
#endif

	for (int i = 0; i < EEPROM_EFFECT_LENGTH; i++)
	{
		EFFECT_NAME[i] = EEPROM.read(EEPROM_ADDRESS_EFFECT + i);
	}

	EFFECT_NAME[EEPROM_EFFECT_LENGTH] = '\0';

	if (ledLine.setEffectByName(EFFECT_NAME))
	{
		ledLine.resume();
	}

	Serial.print(F("LOADED: ")); Serial.println(EFFECT_NAME);
}

void saveEffect()
{
	strncpy(EFFECT_NAME, (ledLine.getEffectName() == nullptr || !ledLine.isRunning()) ? "OFF" : ledLine.getEffectName(), EEPROM_EFFECT_LENGTH);

#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(EEPROM_EFFECT_LENGTH + 1);
#endif

	for (uint8_t i = 0; i < EEPROM_EFFECT_LENGTH + 1; i++)
	{
		EEPROM.write(EEPROM_ADDRESS_EFFECT + i, EFFECT_NAME[i]);
	}
#if defined(ESP32) || defined(ESP8266)
	EEPROM.commit();
#endif

	ledLine.pause();

	Serial.print(F("SAVED: ")); Serial.println(EFFECT_NAME);
}

void changeEffect()
{
	if (ledLine.setNextEffect() && !ledLine.isRunning())
	{
		ledLine.resume();
	}

	Serial.print(F("EFFECT: "));
	Serial.println(ledLine.getEffectName());
}

void turnOffLeds()
{
	ledLine.pause();
	FastLED.clear(true);

	Serial.println(F("OFF"));
}

void adjustBrightness()
{
	brightness += MIN_BRIGHTNESS;
	if (brightness > MAX_BRIGHTNESS + MIN_BRIGHTNESS * 2)
	{
		brightness = 0;
	}
	FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));

	Serial.print(F("BRIGHTNESS: ")); Serial.println(brightness);
}

void handleButtonEvent(const Denel_Button* button, BUTTON_EVENT eventType)
{
	switch (eventType)
	{
	case BUTTON_EVENT::Clicked:
		changeEffect();
		break;
	case BUTTON_EVENT::DoubleClicked:
		saveEffect();
		break;
	case BUTTON_EVENT::RepeatClicked:
		adjustBrightness();
		break;
	case BUTTON_EVENT::LongPressed:
		turnOffLeds();
		break;
	default:
		break;
	}
}

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

	setupLED();

	pinMode(BTN_PIN, INPUT_PULLDOWN_16);
	btn.setEventHandler(handleButtonEvent);

	loadEffect();
}

void loop()
{
	btn.check();

	if (ledLine.refresh())
	{
		FastLED.show();
	}
}


