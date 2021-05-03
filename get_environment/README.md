# Get runtime environment information

* [esduino](https://mmerlin.github.io/esduino/) github.io pages.

* Features
  * Report information about the ESP32 board and resource usage
  * [Template code](#link_template_code) to access runtime environment details
  * ESP32 or ESP8266 board

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

This sketch uses (only) ESPClass methods to access various pieces of information about the running environment. This includes details about the resources currently being used, as well as the capabilities of the hardware module. See the [esp.h](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Esp.h) header file for the latest official function definitions and [esp.cpp](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Esp.cpp) for the actual code.

An ESP8266 reference for [EspClass](https://links2004.github.io/Arduino/d4/dd2/class_esp_class.html) exists that is close to ESP32. The class includes additional methods that can do a lot more than collect information. The reference shows the member names and parameters, but nothing useful about what the methods do. The only ESP32 specific documentation my searches found, was a site that published the [doxygen](https://github.com/doxygen/doxygen) [generated from the code](https://lang-ship.com/reference/ESP32/latest/class_esp_class.html). The website is in Japanese, but the doxygen output is english. Feeding the individual website page URLs through google translate does a decent job of translating the titles from the website.

* [EspClass class](https://translate.google.com/translate?sl=auto&tl=en&u=https://lang-ship.com/reference/ESP32/latest/class_esp_class.html)
* [deepSleep()](https://translate.google.com/translate?sl=auto&tl=en&u=https://lang-ship.com/reference/ESP32/latest/class_esp_class.html%23ac85a1d9fce382cca9b3bc98ed6d01fad)

It seems easier to just look at the raw .h and .cpp files in the links above.

## <a name="link_template_code">⚓</a> Access runtime details template code

This code should be able to be merged into most projects by directly copying the `getEnvironment()` function and `macaddress_t` definition. The `getESP32ChipId()` and `flashModeName()` functions will be needed as well, if those details are desired. No extra library or include file is needed.

[View File](https://github.com/mMerlin/esduino/blob/main/get_environment/get_environment.ino) ¦ [Download](get_environment.ino) ¦ [raw](https://raw.githubusercontent.com/mMerlin/esduino/main/get_environment/get_environment.ino)
