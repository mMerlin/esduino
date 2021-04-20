/* Connect ESP32 or ESP8266 to local wireless access point

  Sketch that can be used to establish a connection to a WiFi access point
  that will be `remembered`, so that later «re»connection attempts by the
  same board, to the same AP, will not need credential information.
*/
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
// secrets.h is not included in the project repository. To set up your own
// project, copy template_secrets.h to secrets.h, then fill in the details
// for your local environment in secrets.h.
#include "secrets.h"

const unsigned long PROGRESS_RATE = 100; // 'in progress' indicator each .1 sec
const unsigned long DISCONNECT_WAIT = 5000; // pause before disconnect
const unsigned long SERIAL_BAUD = 115200;

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial.available()) {delay(10);} // Wait until Serial is really ready
  Serial.println(F("Starting connection attempt"));

  attemptConnection(WIFI_SSID, WIFI_PASSWORD); // use credentials from secrets.h

  delay(DISCONNECT_WAIT);
  Serial.println(F("Disconnect from Wireless access point after setup complete"));
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
}

/**
 * establish connection to wireless access point with specified credentials
 *
 * The connection information is stored in flash, so reconnection can be done
 * to the same AP from other sketches on the same board without credentials
 *
 * @param[in] wifiSSID Name of the network access point to connect to
 * @param[in] wifiPassword Authorization password needed to use the access point
 */
void attemptConnection(const char * wifiSSID, const char * wifiPassword)
{
  const static char * PROGRESS_MARKER PROGMEM = ".";
  wl_status_t wifiStatus = WL_NO_SHIELD;
  Serial.println(F("Setting to station mode"));
  WiFi.mode(WIFI_STA);
  while (!(wifiStatus == WL_DISCONNECTED || wifiStatus == WL_IDLE_STATUS)) {
    Serial.print(PSTR(PROGRESS_MARKER));
    delay(PROGRESS_RATE);
    wifiStatus = WiFi.status();
  }

  WiFi.begin(wifiSSID, wifiPassword);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(PSTR(PROGRESS_MARKER));
    delay(PROGRESS_RATE);
  }
  Serial.println();

  reportConnectionDetails();
} // End attemptConnection()

/**
 * Show information about the established connection
 */
void reportConnectionDetails()
{
  const static char * CONN_RPT_FMT PROGMEM = "\n"
    "Connected to WiFi Access Point with signal strength %d\n"
    "Our IP address is: %s\n"
    "Board (Station) MAC Address: %s\n\n";

  Serial.printf_P(PSTR(CONN_RPT_FMT), WiFi.RSSI(),
    WiFi.localIP().toString().c_str(), WiFi.macAddress().c_str());
} // End reportConnectionDetails()
