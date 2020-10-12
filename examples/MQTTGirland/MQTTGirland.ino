#include "src/data_sensitive.h"
#include "src/LEDLine.h"

/*********** WiFi Access Point **************/
#include <ESP8266WiFi.h>

#define WLAN_SSID       _WLAN_SSID_
#define WLAN_PASS       _WLAN_PASS_

/*********** MQTT Server ********************/
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define MQTT_SERVER      _MQTT_SERVER_
#define MQTT_SERVERPORT  _MQTT_SERVERPORT_
#define MQTT_USERNAME    _MQTT_USERNAME_
#define MQTT_KEY         _MQTT_KEY_

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
//WiFiClientSecure client;  // use WiFiClientSecure for SSL

// Setup the MQTT client class by passing in the WiFi client
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT);
//Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY); // and MQTT server and login details.

Adafruit_MQTT_Publish girlandState = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/current/state");
Adafruit_MQTT_Subscribe girlandEffect = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/new/effect", MQTT_QOS_1);
Adafruit_MQTT_Subscribe girlandOnOff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/new/onoff", MQTT_QOS_1);


/*********** Touch Button or physical *******/
#define TOUCH_BUTTON_PIN D0
//#define BTN_PIN D0  // D0 button pin
#include <GyverButton.h>
#if defined(TOUCH_BUTTON_PIN)
GButton touch(TOUCH_BUTTON_PIN, LOW_PULL, NORM_OPEN);
#else
GButton touch(BTN_PIN, HIGH_PULL, NORM_OPEN);
#endif

/*********** RTC DS1307 module **************/
#include <RTClib.h>
#define ANALOG_PIN A0 // RTC battery voltage input
// D1 - SCL; 
// D2 - SDA
RTC_DS1307 rtc;

/*********** WS2812B leds *******************/
#include <FastLED.h>
#define LED_PIN D1    // D1 leds pin (mapped to D5 on NodeMCU !!!)
#define NUM_LEDS 396
#define CURRENT_LIMIT 16000
#define MAX_BRIGHTNESS 300
#define MIN_BRIGHTNESS 30

CRGB leds[NUM_LEDS];

LEDLine ledLine(leds, NUM_LEDS);

uint16_t brightness = MIN_BRIGHTNESS;

void setup_WiFi()
{
    Serial.println();
    Serial.print(F("Connecting to ")); Serial.println(WLAN_SSID);

    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
       would try to act as both a client and an access-point and could cause
       network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID, WLAN_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
        delay(500);
        Serial.print(".");
        digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level but actually the LED is on; this is because it is active low on the ESP-01)
        delay(200);
    }

    Serial.println("");
    Serial.println(F("WiFi connected"));
    WiFi.printDiag(Serial);

    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
}

void setup_RTC()
{
    Serial.println("");
    Serial.println(F("RTC init..."));

    if (!rtc.begin())
    {
        Serial.println(F("Couldn't find RTC"));
        abort();
    }

    if (!rtc.isrunning())
    {
        Serial.println(F("RTC is NOT running!"));
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void setup_LED()
{
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
    FastLED.setBrightness(brightness);
    FastLED.clear(true);
}

void setup_MQTT()
{
    girlandEffect.setCallback(newEffect_callback);
    girlandOnOff.setCallback(onoff_callback);

    mqtt.subscribe(&girlandEffect);
    mqtt.subscribe(&girlandOnOff);
}

void setup()
{
    pinMode(BUILTIN_LED, OUTPUT);       // Initialize the BUILTIN_LED pin as an output

    Serial.begin(115200);

    setup_WiFi();

    setup_MQTT();

    setup_RTC();

    setup_LED();
}

void onoff_callback(uint32_t x)
{
    Serial.print("Hey we're in a onooff callback, the value is: ");
    Serial.println(x);

    switch (x)
    {
    case OFF_CODE:
        FastLED.clear(true);
        // do not break;
    case PAUSE_CODE:
        ledLine.pause();
        break;
    case ON_CODE:
        ledLine.resume();
        break;
    }
}

void newEffect_callback(char* data, uint16_t len)
{
    Serial.print("Hey we're in a new effect callback, the value is: ");
    Serial.println(data);

    if (ledLine.setEffectByName(data))
        ledLine.resume();
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void mqtt_loop()
{
    int8_t ret;

    if (!mqtt.connected())
    {
        Serial.println(F("Connecting to MQTT... "));
        ret = mqtt.connect();
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
            Serial.print("Battery: "); Serial.println(analogRead(ANALOG_PIN));
            if (!girlandState.publish(rtc.now().secondstime()))
            {
                Serial.println(F("Publish Message Failed"));
            }
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

    if (ledLine.paint())
    {
        FastLED.show();
    }

    mqtt_loop();
}
