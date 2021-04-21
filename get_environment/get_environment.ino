/**
  Get hardware and software environment information

  ESP32 has a getEfuseMac() method, but no getChipId() method, the opposite of
  an ESP8266. To use this with an ESP8266, adjustments may be needed. The
  differences should be handled by the conditional compile directives, but no
  ESP8266 module was conveniently available for testing.

  Initial research finds that WiFi needs to be initialized to get the MAC
  address for the ESP8266, to that is currently excluded here. That is not
  part of the EspClass being used for the rest of the reporting.
*/

typedef union {
  uint64_t full;
  // uint32_t words[2];
  // uint16_t shorts[4];
  uint8_t bytes[8];
} macaddress_t;

const unsigned long SERIAL_BAUD = 115200;
const unsigned long REPORT_INTERVAL = 15000; // millis

void setup() {
  Serial.begin(SERIAL_BAUD);
  while (!Serial.available()) {delay(10);} // Wait until Serial is really ready
}

void loop() {
  getEnvironment();

  delay(REPORT_INTERVAL);
}

void getEnvironment()
{
  uint32_t heapSize = ESP.getHeapSize();
  uint32_t heapFree = ESP.getFreeHeap();
  uint32_t heapMin = ESP.getMinFreeHeap();
  uint32_t heapMax = ESP.getMaxAllocHeap();
  uint32_t psramSize = ESP.getPsramSize();
  uint32_t psramFree = ESP.getFreePsram();
  uint32_t psramMin = ESP.getMinFreePsram();
  uint32_t psramMax = ESP.getMaxAllocPsram();
  uint8_t chipRev = ESP.getChipRevision();
  const char * chipModel = ESP.getChipModel();
  uint8_t chipCores = ESP.getChipCores();
  uint32_t cpuMHz = ESP.getCpuFreqMHz();
  uint32_t cycleCount = ESP.getCycleCount();
  const char * sdkVersion = ESP.getSdkVersion();
  uint32_t flashSize = ESP.getFlashChipSize();
  uint32_t flashSpeed = ESP.getFlashChipSpeed();
  FlashMode_t flashMode = ESP.getFlashChipMode();
  uint32_t sketchSize = ESP.getSketchSize();
  uint32_t sketchFree = ESP.getFreeSketchSpace();
  String sketchMD5 = ESP.getSketchMD5();
#if defined(ESP32)
  macaddress_t efuseMac;
  efuseMac.full = ESP.getEfuseMac();
  uint32_t chipId = getESP32ChipId(efuseMac);
  macaddress_t macAddr2 = efuseMac;
  // Second mac address is the same as the first, with the final bit set
  macAddr2.bytes[5] |= 1;
#elif defined(ESP8266)
  uint32_t chipId = getChipId();
#endif

  Serial.printf_P(PSTR("\nEnvironment details\n\n"));
  Serial.printf_P(PSTR("Heap: size %u(0x%x), free %u(0x%x), min %u(0x%x), max %u(0x%x)\n"),
    heapSize, heapSize, heapFree, heapFree, heapMin, heapMin, heapMax, heapMax);
  Serial.printf_P(PSTR("External (parallel SPI) ram: size %u(0x%x), free %u(0x%x), min %u(0x%x), max %u(0x%x)\n"),
    psramSize, psramSize, psramFree, psramFree, psramMin, psramMin, psramMax, psramMax);
  Serial.printf_P(PSTR("Chip: Model %s, rev %u, %u cores, %u MHz, id %u(0x%x), cycles %u(0x%x)\n"),
    chipModel, chipRev, chipCores, cpuMHz, chipId, chipId, cycleCount, cycleCount);
  Serial.printf_P(PSTR("SDK: %s\n"), sdkVersion);
  Serial.printf_P(PSTR("Flash: size %u(0x%x), SPI speed %u(0x%x), mode %u(%s)\n"),
    flashSize, flashSize, flashSpeed, flashSpeed, flashMode, flashModeName(flashMode));
  Serial.printf_P(PSTR("Sketch: size %u(0x%x), free %u(0x%x), MD5 %s\n"),
    sketchSize, sketchSize, sketchFree, sketchFree, sketchMD5.c_str());
#if defined(ESP32)
  Serial.printf_P(PSTR("Efuse MAC  : %llu(%llx) %02x:%02x:%02x:%02x:%02x:%02x\n"),
    efuseMac.full, efuseMac.full,
    efuseMac.bytes[0], efuseMac.bytes[1], efuseMac.bytes[2],
    efuseMac.bytes[3], efuseMac.bytes[4], efuseMac.bytes[5]);
  // esptool.py read_mac ¦ MAC: fc:f5:c4:16:32:fc
  Serial.printf_P(PSTR("Soft AP MAC: %llu(%llx) %02x:%02x:%02x:%02x:%02x:%02x\n"),
    macAddr2.full, macAddr2.full,
    macAddr2.bytes[0], macAddr2.bytes[1], macAddr2.bytes[2],
    macAddr2.bytes[3], macAddr2.bytes[4], macAddr2.bytes[5]);
#endif
} // end getEnvironment()

/**
  get ESP32 chip ID

  The true ESP32 chip ID is essentially its MAC address.
  This provides an alternate chip ID that matches
  the output of the ESP.getChipId() function on ESP8266
  (i.e. a 32-bit integer matching the last 3 bytes of
  the MAC address). This is less unique than the
  MAC address chip ID, but is helpful when you need
  an identifier that can be no more than a 32-bit integer
  (like for switch...case).

  @return low 24 bits of mac address
*/
uint32_t getESP32ChipId(macaddress_t chipMac)
{
  return (chipMac.bytes[3] << 16) | (chipMac.bytes[4] << 8) | chipMac.bytes[5];
} // end getESP32ChipId()

/**
 * convert flash mode enum to string represenstation
 *
 * @param[in] mode flash mode enum
 * @return string representation of flash mode value
 */
const char * flashModeName(FlashMode_t mode)
{
  switch (mode) {
    case FM_QIO:
      return PSTR("QIO");
      break;
    case FM_QOUT:
      return PSTR("QOUT");
      break;
    case FM_DIO:
      return PSTR("DIO");
      break;
    case FM_DOUT:
      return PSTR("DOUT");
      break;
    case FM_FAST_READ:
      return PSTR("FAST READ");
      break;
    case FM_SLOW_READ:
      return PSTR("SLOW READ");
      break;
    default:
      return PSTR("UNKNOWN");
      break;
  }
  return PSTR("ERROR");
} // end flashModeName()
