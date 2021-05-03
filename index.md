# Index

* [WiFi](#link_wifi_provisioning) ¦ setting up and managing connections
* [environment](#link_environment) ¦ hardware and software environment information
* [Time](#link_time) ¦ setting and using time
* [free RTOS](#link_free_rtos) ¦ working with tasks and cores

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

## <a name="link_wifi_provisioning">⚓</a> WiFi Provisioning

Setting up and managing wireless Internet connections.

* [credentials](#link_ap_credentials)
* [SmartConfig](#link_smartconfig)
* [WPS](#link_wps) «WiFi Protected Setup»
* autoconnect
* Espressif provisioning API

<!--
* [Link](#link_link)
### <a name="link_link">⚓</a> Link
-->

### <a name="link_ap_credentials">⚓</a> Access Point Credentials

* [just_connect_wifi_ap](just_connect_wifi_ap/) ¦ [repository folder](https://github.com/mMerlin/esduino/tree/main/just_connect_wifi_ap/)
  * Template code for establishing an initial connection to the local wireless access point.
  * Once local credentials are filled in, this can be used as a stand-alone sketch to create the initial connection. Unless the credentials change (password change, or move to a different AP), this only needs to be run once. The ESP32 saves the details in flash memory, and later connections can simple 'reconnect'. See [no_credentials_reconnect](no_credentials_reconnect/).
  * Other features
    * private (local environment) data stored only in secrets.h file
    * Use `.gitignore` to exclude the secrets.h file from shared repositories
    * Demonstration of [include guard](https://en.wikipedia.org/wiki/Include_guard)
    * template for creating secrets.h

* [no_credentials_reconnect](no_credentials_reconnect/)
  * Template code for reestablishing a WiFi connection once the information is stored in flash memory. See [just_connect_wifi_ap](just_connect_wifi_ap/)

### <a name="link_smartconfig">⚓</a> SmartConfig

* [Espressif network api](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_smartconfig.html)
* Arduino Examples ¦ Examples for Adafruit ESP32 Feather ¦ WiFi ¦ WiFiSmartConfig
  * [demo](http://www.iotsharing.com/2017/05/how-to-use-smartconfig-on-esp32.html)

This uses a smart phone or tablet app to broadcast credentials information to an un-provisioned device. Information seen so far says that this in an insecure provisioning channel. The credentials seem to be sent un-encrypted over the air. Simple packet sniffing should be able to capture the information. That is slightly mitigated by the data only being transmitted when requested by the (cell phone) user. There is no reason to expect the packets, since they will only exist when smart configure is being used, and only long enough to provision a new device. Not tested (yet), and no documentation seen, but this should be able to be combined with [no_credentials_reconnect](no_credentials_reconnect/), so the configuration only needs to be done once per devices. Once initially provisioned, the information should be stored in flash memory, which is not affected by power cycling, or uploading new sketches.

### <a name="link_wps">⚓</a> WPS

* [Wi-FI Protected Setup (WPS) is Insecure: Here’s Why You Should Disable It](https://www.howtogeek.com/176124/wi-fi-protected-setup-wps-is-insecure-heres-why-you-should-disable-it/)

## <a name="link_environment">⚓</a> Hardware and Software run time environment information

* [get_environment](get_environment/) ¦ [repository folder](https://github.com/mMerlin/esduino/tree/main/get_environment/)
  * Template code to collect (and report) information about the runtime board and software environment

## <a name="link_time">⚓</a> Time

* [set_time_using_ntp](set_time_using_ntp/) ¦ [repository folder](https://github.com/mMerlin/esduino/tree/main/set_time_using_ntp/)
  * Template code to set the internal clock from internet time server

## <a name="link_free_rtos">⚓</a> free RTOS

RTOS : Real Time Operating System

* [Multiple Blink](rtos_blink01/) directly translated from basic Arduino Blink
* [Multiple Blink](rtos_blink02/) refactored to pass unique data to each task with common code

<!--
* [Link](#link_link)
### <a name="link_link">⚓</a> Link
-->
