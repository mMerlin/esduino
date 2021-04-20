# esduino

Sample and template code with descriptions and notes for esp32 modules using Arduino code

* [WiFi](#link_wifi) ¦ setting up and managing connections

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

* [just_connect_wifi](just_connect_wifi/just_connect_wifi.ino)
  * Template code for establishing an initial connection to the local wireless access point.
  * Once local credentials are filled in, this can be used as a stand-alone sketch to create the initial connection. Unless the credentials change (password changed, or move to a different AP), this only needs to be run once. The ESP32 saves the details in flash memory, and later connections can simple 'reconnect'. See `no_credentials_reconnect` below.
  * Other features
    * private (local environment) data stored only in secrets.h file
    * Use `.gitignore` to exclude the secrets.h file from shared repositories
    * Demonstration of include guard
    * template for creating secrets.h

* [no_credentials_reconnect]
  * Template code for reestablishing a WiFi connection once the information is stored in flash memory

* Pending
  * other methods of supplying AP credentials at run time
