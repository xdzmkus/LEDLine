#if defined(ESP32) || defined(ESP8266)
#define LED_PIN D1    // D1 leds pin (mapped to D5 on NodeMCU !!!)
#define BTN_PIN D0    // D0 button pin
#else
#define LED_PIN 9   // leds pin
#define BTN_PIN 10  // button pin
#endif

#include <EEPROM.h>
#define EEPROM_ADDRESS_EFFECT 0
#define EEPROM_EFFECT_LENGTH 15

#include <Denel.h>
using namespace denel;
Button btn(BTN_PIN, BUTTON_CONNECTED::VCC, BUTTON_NORMAL::OPEN);

#include <FastLED.h>
#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 300
#define MIN_BRIGHTNESS 30

CRGB leds[NUM_LEDS];

#include "LEDLine.h"

LEDLine ledLine(leds, NUM_LEDS);

uint16_t brightness = MIN_BRIGHTNESS;

char EFFECT_NAME[EEPROM_EFFECT_LENGTH + 1];

void handleButtonEvent(const Button* button, BUTTON_EVENT eventType)
{
	switch (eventType)
	{
	case BUTTON_EVENT::Clicked:
		ledLine.setNextEffect();
		ledLine.resume();
		Serial.print(F("NEXT: ")); Serial.println(ledLine.getEffectName());
		break;
	case BUTTON_EVENT::DoubleClicked:
		ledLine.pause();
		save();
		Serial.println(F("SAVED"));
		break;
	case BUTTON_EVENT::RepeatClicked:
		brightness -= 20;
		if (brightness > MAX_BRIGHTNESS)
			brightness = MAX_BRIGHTNESS;
		FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, 255));
		FastLED.show();
		break;
	case BUTTON_EVENT::LongPressed:
		ledLine.pause();
		FastLED.clear(true);
		Serial.println(F("OFF"));
		break;
	default:
		break;
	}
}

void setupLED()
{
	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(brightness);
	FastLED.clear(true);
}

void setup()
{
	Serial.begin(115200);
	while (!Serial); // wait for serial port to connect. Needed for native USB
	Serial.println(F("LEDLine effects:"));
	for (auto var : ledLine.availableEffects)
		Serial.println(var);

	setupLED();

	load();

	btn.setEventHandler(handleButtonEvent);
}

void loop()
{
	btn.check();

	if (ledLine.paint())
	{
		FastLED.show();
	}
}

void save()
{
	const char* effect = ledLine.getEffectName();

	if (effect == nullptr) return;

#if defined(ESP32) || defined(ESP8266)
	uint8_t len = min<size_t>(strlen(effect), EEPROM_EFFECT_LENGTH);
	EEPROM.begin(len + 1);
#else
	uint8_t len = min(strlen(effect), EEPROM_EFFECT_LENGTH);
#endif

	EEPROM.write(EEPROM_ADDRESS_EFFECT, len);
	for (uint8_t i = 0; i < len; i++)
	{
		EEPROM.write(EEPROM_ADDRESS_EFFECT+1 + i, effect[i]);
	}
#if defined(ESP32) || defined(ESP8266)
	EEPROM.commit();
#endif
};

void load()
{
#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(EEPROM_EFFECT_LENGTH);
#endif
	uint8_t len = EEPROM.read(EEPROM_ADDRESS_EFFECT);

	if (len > EEPROM_EFFECT_LENGTH) return;

	for (int i = 0; i < len; i++)
	{
		EFFECT_NAME[i] = EEPROM.read(EEPROM_ADDRESS_EFFECT+1 + i);
	}
	EFFECT_NAME[len] = '\0';

	if (ledLine.setEffectByName(EFFECT_NAME))
	{
		ledLine.resume();
	}
};
