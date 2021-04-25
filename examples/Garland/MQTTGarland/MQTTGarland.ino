#if true // && __has_include("my_data_sensitive.h")
#include "my_data_sensitive.h"
#else

#define WLAN_SSID           "AP wifi name"
#define WLAN_PASS           "and password"
#define WLAN_HOSTNAME       "set hostname"

#define MQTT_SERVER         "127.0.0.1"
#define MQTT_SERVERPORT     1883
#define MQTT_USERNAME       "your mqtt username"
#define MQTT_KEY            "and password"

#define MQTT_TOPIC_PUB      MQTT_USERNAME"/get/state"
#define MQTT_TOPIC_SUB1     MQTT_USERNAME"/set/effect"
#define MQTT_TOPIC_SUB2     MQTT_USERNAME"/set/action"

#define ON_CODE             6735
#define OFF_CODE            2344
#define NEXT_CODE           2747

#endif

#define LED_PIN D3    // D1 leds pin (connected to D5 on my NodeMCU 1.0 !!!)

#define BTN_PIN 16    // D0 - GPIO16 - touch button pin

#define UNPINNED_ANALOG_PIN A0 // not connected analog pin

/*********** WS2812B leds *******************/
#include <FastLED.h>
#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20
#define EFFECT_DURATION_SEC 45

uint16_t brightness = MIN_BRIGHTNESS;

CRGB leds[NUM_LEDS];

/*********** LED Line Effects ***************/
#include "LEDLine256.h"
LEDLine256 ledLine(leds, NUM_LEDS);

#include <Ticker.h>
Ticker effectsTicker;
Ticker ledTicker;
Ticker mqttTicker;

volatile boolean f_publishState = true;

/*********** WiFi Client ********************/
#include <WiFiManager.h>

/*********** MQTT Server ********************/
#include <WiFiClient.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;  // use WiFiClientSecure for SSL

// Setup the MQTT client class by passing in the WiFi client
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);
Adafruit_MQTT_Publish   garlandState(&mqtt, MQTT_TOPIC_PUB);
Adafruit_MQTT_Subscribe garlandEffect(&mqtt, MQTT_TOPIC_SUB1, MQTT_QOS_1);
Adafruit_MQTT_Subscribe garlandAction(&mqtt, MQTT_TOPIC_SUB2, MQTT_QOS_1);

/********************************************/

void turnOnLeds()
{
    effectsTicker.detach();

    ledLine.setEffectByIdx(0);
    ledLine.turnOn();

    effectsTicker.attach(EFFECT_DURATION_SEC, changeEffect);

    f_publishState = true;
}

void turnOffLeds()
{
    effectsTicker.detach();

    ledLine.turnOff();

    f_publishState = true;
}

void changeEffect()
{
    effectsTicker.detach();

    ledLine.setNextEffect();

    effectsTicker.attach(EFFECT_DURATION_SEC, changeEffect);

    f_publishState = true;
}

void adjustBrightness()
{
    brightness += MIN_BRIGHTNESS;
    if (brightness > MAX_BRIGHTNESS + MIN_BRIGHTNESS * 2)
    {
        brightness = 0;
    }
    FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
}

void setAction_callback(uint32_t x)
{
    Serial.print(F("new action requested: "));
    Serial.println(x);

    switch (x)
    {
    case ON_CODE:
        turnOnLeds();
        break;
    case OFF_CODE:
        turnOffLeds();
        break;
    case NEXT_CODE:
        changeEffect();
        break;
    default:
        f_publishState = true;
        break;
    }
}

void setEffect_callback(char* data, uint16_t len)
{
    Serial.print(F("new effect requested: "));
    Serial.println(data);

    if (ledLine.setEffectByName(data))
    {
        effectsTicker.detach();
    }

    f_publishState = true;
}

void pingMQTT()
{
    if (!mqtt.connected())
    {
        uint8_t ret(mqtt.connect());

        Serial.println(F("Connecting to MQTT... "));
        if (ret != 0)
        {
            Serial.println(mqtt.connectErrorString(ret));
            Serial.println(F("Retry MQTT connection ..."));
            mqtt.disconnect();
            return;
        }
        else
        {
            Serial.println(F("MQTT Connected!"));
        }
    }

    mqtt.ping();
}

void processMQTT()
{
    mqtt.processPackets(10);

    if (f_publishState && mqtt.connected())
    {
        auto currentEffect = (ledLine.getEffectName() == nullptr || !ledLine.isOn()) ? "OFF" : ledLine.getEffectName();

        Serial.print(F("Publish message: "));
        Serial.println(currentEffect);

        if (!garlandState.publish(currentEffect))
        {
            Serial.println(F("Publish Message Failed"));
            return;
        }

        f_publishState = false;
    }
}

void blinkLED()
{
    //toggle LED state
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup()
{
    randomSeed(analogRead(UNPINNED_ANALOG_PIN));

    pinMode(BTN_PIN, INPUT_PULLDOWN_16); // Re-Initialize the BUTTON pin as an input pulldown

    pinMode(LED_BUILTIN, OUTPUT);        // Initialize the BUILTIN_LED pin as an output
    ledTicker.attach_ms(500, blinkLED);  // Blink led while setup

    Serial.begin(115200);

    setup_LED();

    delay(5000);

    bool resetWiFi = digitalRead(BTN_PIN);

    setup_WiFi(resetWiFi);

    setup_MQTT();

    turnOnLeds();

    ledTicker.detach();
    digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off by making the voltage HIGH
}

void setup_LED()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
    FastLED.clear(true);
}

void setup_WiFi(bool setupMode)
{
    WiFi.mode(WIFI_STA);                // Set the ESP8266 to be a WiFi-client
    WiFi.hostname(WLAN_HOSTNAME);

    Serial.println(WLAN_HOSTNAME);

    WiFiManager wm;

    if (setupMode)
    {
        Serial.println(F("Reset WiFi settings"));

        wm.resetSettings();             // Reset settings - wipe credentials for reconfiguration
    }

    if (!wm.autoConnect(WLAN_SSID, WLAN_PASS))
    {
        Serial.println(F("Connection Failed! Rebooting..."));
        delay(5000);
        ESP.restart();
    }

    Serial.println(F("WiFi connected"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
}

void setup_MQTT()
{
    garlandEffect.setCallback(setEffect_callback);
    mqtt.subscribe(&garlandEffect);

    garlandAction.setCallback(setAction_callback);
    mqtt.subscribe(&garlandAction);

    mqttTicker.attach_scheduled(10.0, pingMQTT);
}

void loop()
{   
    processMQTT();

    if (ledLine.refresh())
    {
        FastLED.show();
    }
}
