#define LED_PIN 9   // led pin
#define BTN_PIN 10  // button pin

#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 300
#define MIN_BRIGHTNESS 50

#include <EEPROM.h>

#define EEPROM_ADDRESS_EFFECT 0
#define EEPROM_ADDRESS_BRIGHTNESS 1

#include <FastLED.h>
#include <LEDStrip.h>

#include <GyverButton.h>
GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);


CRGB leds[NUM_LEDS];

LEDStrip ledStrip(leds, NUM_LEDS);

uint16_t brightness = MIN_BRIGHTNESS;

void setup()
{
	randomSeed(analogRead(0));

#if defined(ESP32) || defined(ESP8266)
	EEPROM.begin(2);
#endif
	ledStrip.load(EEPROM_ADDRESS_EFFECT);
	brightness = EEPROM.read(EEPROM_ADDRESS_BRIGHTNESS);

	FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
	FastLED.setBrightness(brightness);
	FastLED.clear(true);

	touch.setTimeout(300);
	touch.setStepTimeout(50);

	Serial.begin(115200);
	Serial.println(F("LEDStrip"));
}

void loop()
{
	touch.tick();

	if (touch.hasClicks())
	{
		switch (touch.getClicks())
		{
		case 1:
			ledStrip.nextMode();
			FastLED.show();
			break;
		case 2:
			ledStrip.turnOFF();
			FastLED.show();
			break;
		case 3:
			ledStrip.turnON();
			FastLED.show();
			break;
		case 4:
			ledStrip.save(EEPROM_ADDRESS_EFFECT);
#if defined(ESP32) || defined(ESP8266)
			EEPROM.write(EEPROM_ADDRESS_BRIGHTNESS, constrain(brightness, MIN_BRIGHTNESS, 255));
			EEPROM.commit();
#else
			EEPROM.update(EEPROM_ADDRESS_BRIGHTNESS, constrain(brightness, MIN_BRIGHTNESS, 255));
#endif
			ledStrip.turnFlashes();
			FastLED.show();
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
	
	if (ledStrip.isUpdated())
	{
		FastLED.show();
	}
}
