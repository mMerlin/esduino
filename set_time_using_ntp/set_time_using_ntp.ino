/*
  Get current time from NTP (Network Time Protocol) server

  use template code from `no_credentials_reconnect` for wifi access
*/
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <time.h>
#include "secrets.h"

const unsigned long PROGRESS_RATE = 100; // 'in progress' indicator each .1 sec
const unsigned long SERIAL_BAUD = 115200;

// Time processing information
const char *ntpServer PROGMEM = NTP_SERVER;
const long  utcOffset_sec = UTC_OFFSET_SEC;
const int   daylightOffset_sec = DAYLIGHT_OFFSET_SEC;

const unsigned long TIME_REPORT_INTERVAL = 1000;

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial.available()) {delay(10);} // Wait until Serial is really ready
  Serial.println(F("Starting no credentials connection attempt"));

  attemptConnection();

  // initialize the internal time
  configTime(utcOffset_sec, daylightOffset_sec, PSTR(ntpServer));
  printLocalTime(); // causes delay until (usually) the time has been obtained

  Serial.println(F("Disconnect from Wireless access point after setup complete"));
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  printLocalTime();
  delay(TIME_REPORT_INTERVAL);
}

// Time handling functions

/**
 * get local time stamp information
 *
 * @param[out] outTime raw (binary) time information
 * @return true when successfully obtained a local time value
 */
bool freshLocalTime(struct tm * outTime)
{
  if(!getLocalTime(outTime)){
    Serial.println(F("Failed to obtain fresh time"));
    return false;
  }
  return true;
}

void printLocalTime()
{
  const static char TIME_FORMAT[] PROGMEM = "%A, %B %d %Y %H:%M:%S";
  struct tm tmInfo;
  char tmText [38]; // max: "Wednesday, September 30 2000 00:00:00\0"

  if (freshLocalTime(&tmInfo)) {
    size_t tmLen = strftime(tmText, sizeof tmText, PSTR(TIME_FORMAT), &tmInfo);
    if (tmLen > 0) {
      Serial.printf_P(PSTR("The time is now %s\n"), tmText);
    } else {
      Serial.println(F("Overflow of time data buffer"));
    }
  }
}

// WiFi handling functions

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
