#pragma once

#include <Arduino.h>

/*
 *  Constants
 */
#define SERIAL_BAUD_RATE 115200
#define ON LOW
#define OFF HIGH

/*
 * Configuration
 */
#define BLYNK_ENABLED // Comment this line in order to disable Blynk integration
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxxxxxxxxxx-xxxxx"
#define ALEXA_ENABLED // Comment this line in order to disable Amazon Alexa integration
#define SINRIC_APP_KEY "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
#define SINRIC_APP_SECRET "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx-xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
#define SINRIC_SWITCH_ID "xxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxx"
#define RELAY_PIN 16 // Be sure to set the same pin on the Blynk app
#define INITIAL_STATE OFF
#define DISCONNECTED_STATE ON
