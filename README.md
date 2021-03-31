# Smart Switch

Using Blynk and Amazon Alexa with the ESP01 Relay Module.

All configuration is placed on `SmartSwitch/include/SmartSwitch.hpp`, please check this file before anything else.

## Setting up with Blynk

If you desire to disable Blynk, just comment the `#define BLYNK_ENABLED` line on `SmartSwitch/include/SmartSwitch.hpp`.

- Download and install Blynk on your smartphone
- Create a new app
- Place a button with Switch mode and set it to `GP0` (or the pin you want to use for your relay)
- Get your Blynk key from e-mail and replace it on the `SmartSwitch/include/SmartSwitch.hpp` file

## Setting up with Amazon Alexa

If you desire to disable Amazon Alexa, just comment the `#define ALEXA_ENABLED` line on `SmartSwitch/include/SmartSwitch.hpp`.

- Create an account on SinricPro
- Add a new Device of type Switch
- On the "Credentials" tab, get both of your app key and password
- On the "Devices" tab, get your device ID
- Fill it up on `SmartSwitch/include/SmartSwitch.hpp`

## Initial state and state if device goes offline

On `SmartSwitch/include/SmartSwitch.hpp`, set it like this:

```cpp
#define INITIAL_STATE OFF
#define DISCONNECTED_STATE ON
```