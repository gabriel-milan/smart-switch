/*
 *  Includes
 */
#include <ESP8266WiFi.h>   // So we can connect to the Wi-Fi
#include <SmartSwitch.hpp> // SmartSwitch configuration
#ifdef BLYNK_ENABLED
#include <BlynkSimpleEsp8266.h> // So we can use Blynk
#endif
#ifdef ALEXA_ENABLED
#include <SinricPro.h> // So we can use Alexa
#include <SinricProSwitch.h>
#endif

// Keeps track of connection state
wl_status_t lastWifiStatus;

/*
 * Function for connecting to Wi-Fi
 * (cloned from Blynk.connectWiFi)
 */
void connectWiFi(const char *ssid, const char *pass)
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  if (WiFi.status() != WL_CONNECTED)
  {
    if (pass && strlen(pass))
    {
      WiFi.begin(ssid, pass);
    }
    else
    {
      WiFi.begin(ssid);
    }
  }
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.println("Connected to WiFi");
  IPAddress myip = WiFi.localIP();
  (void)myip;
  Serial.print("IP: ");
  Serial.println(myip);
}

#ifdef ALEXA_ENABLED
/*
 * Function for managing switch state with Alexa
 */
bool switchState(const String &deviceId, bool &state)
{
  digitalWrite(RELAY_PIN, state ? ON : OFF);
  return true;
}

/*
 * Function for setting SinricPro up
 */
void setupSinricPro()
{
  // Add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch = SinricPro[SINRIC_SWITCH_ID];
  mySwitch.onPowerState(switchState);

  // Setup SinricPro
  SinricPro.onConnected([]() { Serial.printf("Connected to SinricPro\r\n"); });
  SinricPro.onDisconnected([]() { Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(SINRIC_APP_KEY, SINRIC_APP_SECRET);
}
#endif

/*
 *  Setup
 */
void setup()
{
  // Initializing Serial
  Serial.begin(SERIAL_BAUD_RATE);
  // Setting relay ping as output
  pinMode(RELAY_PIN, OUTPUT);
  // Setting relay OFF at startup
  digitalWrite(RELAY_PIN, HIGH);
  // Connect to Wi-Fi
  connectWiFi(WIFI_SSID, WIFI_PASSWORD);
#ifdef BLYNK_ENABLED
  // Configure Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
#endif
#ifdef ALEXA_ENABLED
  // Configure SinricPro
  setupSinricPro();
#endif
  // Set initial states
  lastWifiStatus = WiFi.status();
}

/*
 *  Loop
 */
void loop()
{
  // If Wi-Fi is not connected
  if (WiFi.status() != WL_CONNECTED)
  {
    // Lost connection
    if (lastWifiStatus == WL_CONNECTED)
      // Set relay ON so it can be controlled locally
      digitalWrite(RELAY_PIN, LOW);
    // Log connection state and retry Wi-Fi connection
    Serial.println("Wi-Fi is not connected, will retry connection...");
    connectWiFi(WIFI_SSID, WIFI_PASSWORD);
  }
#ifdef BLYNK_ENABLED
  // Wi-Fi is connected but Blynk isn't
  else if (!Blynk.connected())
  {
    // Log connection state and retry Blynk connection
    BLYNK_LOG1("Blynk is not connected, will retry connection...");
    Blynk.connect();
  }
#endif
  // Update connection state
  lastWifiStatus = WiFi.status();
#ifdef ALEXA_ENABLED
  SinricPro.handle();
#endif
#ifdef BLYNK_ENABLED
  Blynk.run();
#endif
}