#include "data_sensitive.h"

#define LED_PIN D3    // D1 leds pin (connected to D5 on my NodeMCU 1.0 !!!)

/*********** WiFi Access Point **************/
#include <ESP8266WiFi.h>

#define WLAN_SSID       _WLAN_SSID_
#define WLAN_PASS       _WLAN_PASS_
#define WLAN_HOSTNAME   _WLAN_HOSTNAME_

/*********** MQTT Server ********************/
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define MQTT_SERVER      _MQTT_SERVER_
#define MQTT_SERVERPORT  _MQTT_SERVERPORT_
#define MQTT_USERNAME    _MQTT_USERNAME_
#define MQTT_KEY         _MQTT_KEY_

#define MQTT_TOPIC_PUB MQTT_USERNAME"/current/state"
#define MQTT_TOPIC_SUB1 MQTT_USERNAME"/new/effect"
#define MQTT_TOPIC_SUB2 MQTT_USERNAME"/new/onoff"

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
//WiFiClientSecure client;  // use WiFiClientSecure for SSL

// Setup the MQTT client class by passing in the WiFi client
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);
//Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT);

Adafruit_MQTT_Publish girlandState = Adafruit_MQTT_Publish(&mqtt, MQTT_TOPIC_PUB);
Adafruit_MQTT_Subscribe girlandEffect = Adafruit_MQTT_Subscribe(&mqtt, MQTT_TOPIC_SUB1, MQTT_QOS_1);
Adafruit_MQTT_Subscribe girlandOnOff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_TOPIC_SUB2, MQTT_QOS_1);

/*********** WS2812B leds *******************/
#include <FastLED.h>
#define NUM_LEDS 256
#define CURRENT_LIMIT 8000
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 20

uint16_t brightness = MAX_BRIGHTNESS / 2;

CRGB leds[NUM_LEDS];

#include "LEDLine.h"
LEDLine ledLine(leds, NUM_LEDS);

#include <Ticker.h>
#define EFFECT_DURATION_SEC 60
Ticker tickerEffects;

volatile boolean f_publishState = true;

void handleTimer(void)
{
    if (ledLine.isRunning()) ledLine.setNextEffect();
    f_publishState = true;
}

void onoff_callback(uint32_t x)
{
    Serial.print(F("on/off with code: "));
    Serial.println(x);

    switch (x)
    {
    case OFF_CODE:
        FastLED.clear(true);
        ledLine.pause();
        break;
    case PAUSE_CODE:
        ledLine.pause();
        break;
    case ON_CODE:
        ledLine.resume();
        break;
    default:
        f_publishState = true;
        break;
    }
}

void newEffect_callback(char* data, uint16_t len)
{
    Serial.print(F("new effect requested: "));
    Serial.println(data);

    ledLine.setEffectByName(data);
}

void publishState()
{
    auto currentEffect = (ledLine.getEffectName() == nullptr || !ledLine.isRunning()) ? "OFF" : ledLine.getEffectName();

    Serial.print(F("Publish message: ")); Serial.println(currentEffect);

    if (!girlandState.publish(currentEffect))
    {
        Serial.println(F("Publish Message Failed"));
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);       // Initialize the BUILTIN_LED pin as an output

    Serial.begin(115200);

    setup_WiFi();

    setup_MQTT();

    setup_LED();

    tickerEffects.attach(EFFECT_DURATION_SEC, handleTimer);

    ledLine.resume();
}

void setup_WiFi()
{
    Serial.println();
    Serial.print(F("Connecting to ")); Serial.println(WLAN_SSID);

    WiFi.mode(WIFI_STA);                  // Set the ESP8266 to be a WiFi-client
    WiFi.hostname(WLAN_HOSTNAME);
    WiFi.begin(WLAN_SSID, WLAN_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level but actually the LED is on; this is because it is active low on the ESP-01)
        delay(500);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
        delay(200);
    }

    Serial.println("");
    Serial.println(F("WiFi connected"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
}

void setup_MQTT()
{
    girlandEffect.setCallback(newEffect_callback);
    mqtt.subscribe(&girlandEffect);

    girlandOnOff.setCallback(onoff_callback);
    mqtt.subscribe(&girlandOnOff);
}

void setup_LED()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.setBrightness(constrain(brightness, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
    FastLED.clear(true);
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void mqtt_loop()
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

    mqtt.processPackets(10);
}

void loop()
{
    if (f_publishState)
    {
        f_publishState = false;

        publishState();
    }

    if (ledLine.paint())
    {
        FastLED.show();
    }

    mqtt_loop();
}
