#if defined(ESP8266)
#define LED_PIN D1  // D1 leds pin (connected to D5 on my NodeMCU1.0 !!!)
#define BTN_PIN D0  // 16 button pin
#else
#define LED_PIN 9   // leds pin
#define BTN_PIN 4   // button pin
#define ENC1_PIN 3  // encoder S1 pin
#define ENC2_PIN 2	// encoder S2 pin
#endif

#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

#include <ArduinoDebounceButton.h>
ArduinoDebounceButton btn(BTN_PIN, BUTTON_CONNECTED::GND, BUTTON_NORMAL::OPEN);

#include "ArduinoRotaryEncoder.h"
#include "EventsQueue.hpp"
ArduinoRotaryEncoder encoder(ENC2_PIN, ENC1_PIN);
EventsQueue<ENCODER_EVENT, 10> queue;

#include <EEPROM.h>
#define EEPROM_ADDRESS_EFFECT 0
#define EEPROM_EFFECT_LENGTH 15

char EFFECT_NAME[EEPROM_EFFECT_LENGTH + 1];

#include <FastLED.h>
#define NUM_LEDS 128
#define CURRENT_LIMIT 8000

uint8_t brightness = 100;

CRGB leds[NUM_LEDS];

#include "LEDLineEx.h"

LEDLineEx ledLine(leds, NUM_LEDS);

void loadState()
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
		Serial.print(F("LOADED EFFECT: "));
	}
	else
	{
		Serial.print(F("WRONG EFFECT: "));
	}

	Serial.println(EFFECT_NAME);

	ledLine.turnOn();
}

void saveState()
{
	strncpy(EFFECT_NAME, (ledLine.getEffectName() == nullptr || !ledLine.isOn()) ? "OFF" : ledLine.getEffectName(), EEPROM_EFFECT_LENGTH);

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

	ledLine.turnOff();

	Serial.print(F("SAVED EFFECT: "));
	Serial.println(EFFECT_NAME);
}

void changeEffect()
{
	ledLine.setNextEffect();
	ledLine.turnOn();

	Serial.print(F("EFFECT: "));
	Serial.println(ledLine.getEffectName());
}

void turnOffLeds()
{
	ledLine.turnOff();
	FastLED.clear(true);

	Serial.println(F("OFF"));
}

void adjustBrightness(int8_t delta)
{
	brightness += delta;
	FastLED.setBrightness(brightness);

	Serial.print(F("BRIGHTNESS: "));
	Serial.println(brightness);
}

void processEncoder()
{
	bool processEncEvent;
	ENCODER_EVENT encEvent;

	do
	{
		noInterrupts();

		processEncEvent = queue.length();

		if (processEncEvent)
		{
			encEvent = queue.pop();
		}

		interrupts();

		if (processEncEvent)
		{
			switch (encEvent)
			{
			case ENCODER_EVENT::LEFT:
				adjustBrightness(-5);
				break;
			case ENCODER_EVENT::RIGHT:
				adjustBrightness(5);
				break;
			default:
				break;
			}
		}
	} while (processEncEvent);

}

void handleButtonEvent(const DebounceButton* button, BUTTON_EVENT eventType)
{
	switch (eventType)
	{
	case BUTTON_EVENT::Clicked:
		changeEffect();
		break;
	case BUTTON_EVENT::DoubleClicked:
		saveState();
		break;
	case BUTTON_EVENT::LongPressed:
		turnOffLeds();
		break;
	default:
		break;
	}
}

void catchEncoderTicks()
{
	encoder.catchTicks();
}

void handleEncoderEvent(const RotaryEncoder* enc, ENCODER_EVENT eventType)
{
	queue.push(eventType);
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

#if defined(ESP8266) && (BTN_PIN == 16)
	pinMode(BTN_PIN, INPUT_PULLDOWN_16);
#else
	btn.initPin();
#endif

	btn.setEventHandler(handleButtonEvent);

	encoder.initPins();

	encoder.setEventHandler(handleEncoderEvent);

	attachInterrupt(digitalPinToInterrupt(2), catchEncoderTicks, CHANGE);
	attachInterrupt(digitalPinToInterrupt(3), catchEncoderTicks, CHANGE);

	loadState();
}

void loop()
{
	btn.check();

	processEncoder();

	if (ledLine.refresh())
	{
		FastLED.show();
	}
}
