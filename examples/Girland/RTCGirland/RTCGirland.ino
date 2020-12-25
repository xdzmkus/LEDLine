#if defined(ESP32) || defined(ESP8266)
#define LED_PIN D1    // D1 leds pin (connected to D5 on my NodeMCU 1.0 !!!)
// #define SCL D1
// #define SDA D2
#else
#define LED_PIN 9   // leds pin
#endif

#define NUM_LEDS 8
#define CURRENT_LIMIT 500
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20

uint16_t brightness = MAX_BRIGHTNESS / 2;

#include <FastLED.h>
CRGB leds[NUM_LEDS];

#include "LEDLine.h"
LEDLine ledLine(leds, NUM_LEDS);

#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
#define ANALOG_PIN A0 // RTC battery voltage input
#define EFFECT_DURATION_SEC 60
uint32_t lastChange = 0;

void setupLED()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
    FastLED.clear(true);
}

void setup_RTC()
{
    Serial.println("");
    Serial.println(F("RTC init..."));

    auto batteryLevel = analogRead(ANALOG_PIN);
    Serial.print(F("Battery level: ")); Serial.println(batteryLevel);

    if (!rtc.begin())
    {
        Serial.println(F("Couldn't find RTC"));
        exit(1);
    }

    if (!rtc.isrunning())
    {
        Serial.println(F("RTC is NOT running!"));
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    DateTime now = rtc.now();

    Serial.print(F("Current date & time: "));
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void setup()
{
    Serial.begin(115200);

    Serial.println(F("LEDLine EFFECTS:"));
    for (auto var : ledLine.availableEffects)
        Serial.println(var);

    setupLED();

    setup_RTC();

    lastChange = rtc.now().secondstime();
 
    ledLine.setNextEffect();
}

void loop()
{
    uint32_t currentTime = rtc.now().secondstime();

    if (currentTime - lastChange > EFFECT_DURATION_SEC)
    {
        lastChange = currentTime;
        ledLine.setNextEffect();
        Serial.print(F("EFFECT: ")); Serial.println(ledLine.getEffectName());
    }

    if (ledLine.paint())
    {
        FastLED.show();
    }
 }