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

#include <GyverButton.h>
#define TOUCH_BUTTON
#if defined(TOUCH_BUTTON)
GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);
#else
GButton touch(BTN_PIN, HIGH_PULL, NORM_OPEN);
#endif

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

			if (receivedBytes == EEPROM_EFFECT_LENGTH)
				receivedBytes = 0;
		}
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
	randomSeed(analogRead(0));

	Serial.begin(115200);
	while (!Serial); // wait for serial port to connect. Needed for native USB
	Serial.println(F("LEDLine effects:"));
	for (auto var : ledLine.availableEffects)
		Serial.println(var);

	touch.setTimeout(300);
	touch.setStepTimeout(50);

	setupLED();

	load();
}

void loop()
{
	touch.tick();

	if (touch.hasClicks())
	{
		switch (touch.getClicks())
		{
		case 1:
			ledLine.setNextEffect();
			ledLine.resume();
			Serial.print(F("NEXT: ")); Serial.println(ledLine.getEffectName());
			break;
		case 2:
			ledLine.pause();
			FastLED.clear(true);
			Serial.println(F("OFF"));
			break;
		case 3:
			ledLine.pause();
			save();
			Serial.println(F("SAVED"));
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

	if (isNewEffect)
	{
		Serial.print(F("NEW_EFFECT:"));	Serial.println(EFFECT_NAME);

		isNewEffect = false;
		if (ledLine.setEffectByName(EFFECT_NAME))
		{
			ledLine.resume();
		}
		else
		{
			Serial.println(F("BAD_EFFECT"));
		}
	}

	if (ledLine.paint())
	{
		FastLED.show();
	}
}


void save()
{
	const char* effect = ledLine.getEffectName();

	if (effect == nullptr) return;

	uint8_t len = min(strlen(effect), EEPROM_EFFECT_LENGTH);

#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(len + 1);
#endif
	EEPROM.update(EEPROM_ADDRESS_EFFECT, len);
	for (uint8_t i = 0; i < len; i++)
	{
		EEPROM.update(EEPROM_ADDRESS_EFFECT+1 + i, effect[i]);
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
