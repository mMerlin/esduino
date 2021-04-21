/* Connect ESP32 or ESP8266 to local wireless access point

  Demonstration of connecting to a WiFi access point without specifying
  credentials. No SSID or password. The authentication will be done using
  authentication information stored in FLASH after a separate sketch
  established a connection using credentials.
*/
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

const unsigned long PROGRESS_RATE = 100; // 'in progress' indicator each .1 sec
const unsigned long DISCONNECT_WAIT = 5000; // pause before disconnect
const unsigned long SERIAL_BAUD = 115200;

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial.available()) {delay(10);} // Wait until Serial is really ready
  Serial.println(F("Starting no credentials connection attempt"));

  attemptConnection();

  delay(DISCONNECT_WAIT);
  Serial.println(F("Disconnect from Wireless access point after setup complete"));
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
}

/**
 * establish connection to wireless access point without specifying credentials
 *
 * The credentials information is read from flash, saved during execution of
 * a previous sketch.
 */
void attemptConnection()
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

  if (!WiFi.reconnect()) {
    Serial.println(F("\nreconnection failed"));
    return;
  }

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
