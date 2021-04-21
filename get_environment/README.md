# Get runtime environment information

* Features
  * Report information about the ESP32 board and resource usage
  * [Template code](#link_template_code) to access runtime environment details
  * ESP32 or ESP8266 board

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

This sketch uses ESPClass methods to access various pieces of information about the running environment. This includes details about the resources currently being used, as well as the capabilities of the hardware module. See the [esp.h](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Esp.h) header file for the latest official function definitions and [esp.cpp](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Esp.cpp) for the actual code.

[Download sketch](https://mmerlin.github.io/esduino/get_environment/get_environment.ino)

There are various tutorials for using specific methods of the ESPClass, but the only documentation of the class my searches found, was a site that published the [doxygen](https://github.com/doxygen/doxygen) [generated from the code](https://lang-ship.com/reference/ESP32/latest/class_esp_class.html). The website is in Japanese, but the doxygen out is english. Feeding the individual website page URLs through google translate does a good job at translating the titles from the website.

* [EspClass class](https://translate.google.com/translate?sl=auto&tl=en&u=https://lang-ship.com/reference/ESP32/latest/class_esp_class.html)
* [deepSleep()](https://translate.google.com/translate?sl=auto&tl=en&u=https://lang-ship.com/reference/ESP32/latest/class_esp_class.html%23ac85a1d9fce382cca9b3bc98ed6d01fad)

It seems easier to just look at the raw .h and .cpp files in the links above.

## <a name="link_template_code">⚓</a> WiFi connection template code

This code should be able to be merged into most projects by directly copying the `getEnvironment()` function and `macaddress_t` definition. The `getESP32ChipId()` and `flashModeName()` functions will be needed as well, if those details are desired. No extra library or include file is needed.
