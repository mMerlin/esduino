# No credentials reconnection

* Features
  * Use credentials automatically stored in flash memory
  * [Template code](#link_template_code) to establish connection to WiFi Access Point
  * ESP32 or ESP8266 board

This sketch can be used to provide template wireless access point (re) connection code for use in other projects. See
[just_connect_wifi_ap](../just_connect_wifi_ap/)
for example and template code for initially connecting using hard-coded credentials.

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

## <a name="link_overview">⚓</a> Overview

The standard WiFi (or ESP8266WiFi) library stores the latest connection credentials in flash memory. A successful WiFi.begin(), will automatically remember the used credentials (SSID and password) in 'permanent' memory. That memory is not erased by resets, power cycling, or uploading new sketches. So multiple sketches that need WiFi access can be uploaded and run, without including any SSID or password, as long as a sketch (like [just_connect_wifi_ap](../just_connect_wifi_ap/)) has been uploaded first to establish the initial connection. On the same ESP board.

This is very useful when doing exploration, testing and development, where multiple different sketches can be uploaded at different times to the same board. Potentially for vastly different purposes. These sketches can be safely shared without worrying about first erasing private information about the access point being used. This is less useful for a project that is to be deployed in the field by someone else. Whoever does the deployment would also need the setup sketch, plus the tools and expertise to set the credentials to match their local environment, and to then upload the actual project sketch. Other options are better for that scenario.

## <a name="link_template_code">⚓</a> WiFi connection template code

This code should be able to be merged into most projects by directly copying the `attemptConnection()` and `reportConnectionDetails()` functions. `WiFi.h` or `ESP8266WiFi.h` needs to be included as well, although that is probably required by the target project anyway.

A connection is created by calling `attemptConnection()` (typically in `setup()`, but other options work too). The required credentials must have been previous saved to flash memory using other code (like [just_connect_wifi_ap](../just_connect_wifi_ap/)).

[View File](https://github.com/mMerlin/esduino/blob/main/no_credentials_reconnect/no_credentials_reconnect.ino) ¦ [Download](no_credentials_reconnect.ino) ¦ [raw](https://raw.githubusercontent.com/mMerlin/esduino/main/no_credentials_reconnect/no_credentials_reconnect.ino)
