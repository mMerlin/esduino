# No credentials reconnection

* Features
  * Use credentials automatically stored in flash memory
  * [Template code](#link_template_code) to establish connection to WiFi Access Point
  * ESP32 or ESP8266 board

This project can be used to provide template wireless access point (re) connection code for use in other projects. See
[just_connect_wifi_ap](../just_connect_wifi_ap/)
for example and template code for initially connecting using hard-coded credentials.

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

## <a name="link_template_code">⚓</a> WiFi connection template code

This code should be able to be merged into most projects by directly copying the `attemptConnection()` and `reportConnectionDetails()` functions. A connection is created by calling `attemptConnection()` (typically in `setup()`, but other options work too). The required credentials must have been previous saved to flash memory using other code (like [just_connect_wifi_ap](../just_connect_wifi_ap/)).
