# Index

* [WiFi](#link_wifi) ¦ setting up and managing connections
* [environment](#link_environment) ¦ hardware and software environment information

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

## <a name="link_wifi">⚓</a> WiFi

Setting up and managing wireless connections.

* [credentials](#link_ap_credentials)

<!--
* [Link](#link_link)
### <a name="link_link">⚓</a> Link
-->

### <a name="link_ap_credentials">⚓</a> Access Point Credentials

* [just_connect_wifi_ap](just_connect_wifi_ap/) ¦ [repository folder](https://github.com/mMerlin/esduino/tree/main/just_connect_wifi_ap/)
  * Template code for establishing an initial connection to the local wireless access point.
  * Once local credentials are filled in, this can be used as a stand-alone sketch to create the initial connection. Unless the credentials change (password changed, or move to a different AP), this only needs to be run once. The ESP32 saves the details in flash memory, and later connections can simple 'reconnect'. See [no_credentials_reconnect](no_credentials_reconnect/).
  * Other features
    * private (local environment) data stored only in secrets.h file
    * Use `.gitignore` to exclude the secrets.h file from shared repositories
    * Demonstration of include guard
    * template for creating secrets.h

* [no_credentials_reconnect](no_credentials_reconnect/)
  * Template code for reestablishing a WiFi connection once the information is stored in flash memory. See [just_connect_wifi_ap](just_connect_wifi_ap/)

## <a name="link_environment">⚓</a> Hardware and Software run time environment information

* [get_environment](get_environment/) ¦ [repository folder](https://github.com/mMerlin/esduino/tree/main/get_environment/)
  * Template code to collect (and report) information about the runtime board and software environment
