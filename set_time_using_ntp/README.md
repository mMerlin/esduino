# Set Time using NTP

* Features
  * use code from [no_credentials_reconnect](../no_credentials_reconnect/) to establish WiFi connection
  * [`secrets.h` include file](#link_secrets)
    * used for local time zone configuration, not WiFi credentials.
  * [.gitignore](#link_git_ignore)
  * [include guard](#link_include_guard)
  * [Template include file](#link_template_secrets) to copy to create personal version of `secrets.h`
  * [Template code](#link_template_code) to initialize clock to time from NTP server
  * ESP32 or ESP8266 board

This sketch can be used to provide template code to set the correct time on the ESP board from an Internet [NTP](https://en.wikipedia.org/wiki/Network_Time_Protocol) server. Setting the time can be done once, using the internal clock to track time from then one, or done on some sort of schedule, to keep the time closer to the official time servers.

* [Time Reference Information](#link_reference)

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

## <a name="link_reference">⚓</a> Time Reference Information

* [ntp.org](https://www.ntp.org) ¦ home of the Network Time Protocol project
* [How do I use pool.ntp.org](https://www.ntppool.org/en/use.html)
* [NTP Server: Free Public Internet Time Servers](https://timetoolsltd.com/information/public-ntp-server/)
* [Timezone offset](https://www.epochconverter.com/timezones)
  * this reference shows the daylight time offset, so adjust for that before using here
* [GMT – Greenwich Mean Time / Coordinated Universal Time (Standard Time)](https://www.timeanddate.com/time/zones/gmt)
  * multiple hours by 3600 to get the seconds offset needed for configuration

## <a name="link_secrets">⚓</a> Configuration in `secrets.h`

In [just_connect_wifi_ap](../just_connect_wifi_ap/), `secrets.h` is used to store the private local credentials (login information) needed to access a local WiFi access point. The information stored in `secrets.h` for this sketch does not meed to be as "private". It is local configuration information about the timezone and daylight savings time offset to use when determining the local time. If you do not care about people knowing what time zone you (or at least your project) is in, the stored values could be hard-coded right in the sketch. The problem with that, for shared projects, is that the code then becomes (unnecessarily) different for each implementation.

That means moving the local configuration details out of the sketch, and into a separate included file makes the shared projects cleaner. On ESP boards, that could be a data file (stored in [SPIFFS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/spiffs.html)). That solution may be demonstrated later. This template code is designed to load the information from an include file. Using something like `local_time.h` or `my_time_zone.h` would work fine. Just be careful not to use something like `time.h`, which would conflict with the standard time library. Using a normal include header file has, to a lesser extent, the same problem as hard-coding the values in the sketch file. Share projects would thing become different, just to handle the local configuration. Those example include files names are not `special`, and would normally be shared with the project.

Since the `secrets.h` file, and the definitions it provides, are still needed to use the project, a [Template include file](#link_template_secrets) and instructions should be provided with the project.

### <a name="link_git_ignore">⚓</a> .gitignore file

Specifying the timezone details in the `secrets.h` file is not enough to keep shared projects from being 'different', if the secrets file is included in a repository that is shared publicly. To prevent that small difference, a `.gitignore` file can be added to the git repository that marks the `secrets.h` file to be excluded from `add` operations. As long as the `.gitignore` file, with the proper entry, exists before adding new files (after creating secrets.h), git will not offer to automatically save the secrets.h file in the repository. It remains in the local project folder, but is not part of the published repository.

[View File](https://github.com/mMerlin/esduino/blob/main/set_time_using_ntp/.gitignore) ¦ [Download](https://raw.githubusercontent.com/mMerlin/esduino/main/set_time_using_ntp/.gitignore) (right-click + Save Link As)

```.gitignore
# Not to be shared with the project files
secrets.h
```

When using git to share the project, a `.gitignore` file can be included, with an entry to exclude the `secrets.h` file. Since people trying to use the shared project will need their own secrets file, include a [secrets_template.h](#link_template_secrets) file in the project, that contains samples of the needed information, and instructions for copying it to `secrets.h`, and making the needed changes there.

### <a name="link_include_guard">⚓</a> include guard

An [include guard](https://github.com/mMerlin/esduino/wiki/include-guard) is a safety measure, used to prevent the definitions in an included header file from being processed in a project build multiple times.

### <a name="link_template_secrets">⚓</a> template for secrets.h

Since the `secrets.h` file is excluded from shared projects, to hide minor configuration differences between shared projects, a way for other project users to easily create their own version is needed. One way to do that is to provided a template file containing dummy values that need to be replaced. Additional instructions can be provided different places.

* The project README can include project setup instructions
* The template file can include comments about how to use it
* The (main) project code file can include comments with the steps needed to create `secrets.h` from the template file

[View File](https://github.com/mMerlin/esduino/blob/main/set_time_using_ntp/template_secrets.h) ¦ [Download](template_secrets.h) ¦ [raw](https://raw.githubusercontent.com/mMerlin/esduino/main/set_time_using_ntp/template_secrets.h)

```c++
#ifndef MY_SECRETS_H
#define MY_SECRETS_H

// Copy this file to `secrets.h` in the project folder, and replace the dummy
// defined values with those needed for your environment. Do not edit this
// (the template) file. Copy it, then edit the copy. This block
// of comments can optionally be removed from the resulting `secrets.h` file.

// specify the URL of the time server (or pool) you want to use
// pool.ntp.org should work fine in most cases
#define NTP_SERVER "pool.ntp.org"
// local timezone offset fromUTC in seconds when NOT daylight savings time
// this could be either positive or negative, depending on the timezone
#define UTC_OFFSET_SEC (3600*hours_offset)
// #define UTC_OFFSET_SEC (-3600*hours_offset)
// offset (seconds) from above when daylight savings is in effect
#define DAYLIGHT_OFFSET_SEC 0

#endif
```

Information from multiple `secrets.h` template files can be combined without problems. An example of a valid `secrets.h` file containing both both WiFi credentials (as used for [just_connect_wifi_ap](../just_connect_wifi_ap/)) and time zone configuration could be:

```c++
#ifndef MY_SECRETS_H
#define MY_SECRETS_H

#define WIFI_SSID "my_home_access_point"
#define WIFI_PASSWORD "the_ap_password"

#define NTP_SERVER "pool.ntp.org"
#define UTC_OFFSET_SEC -3600
#define DAYLIGHT_OFFSET_SEC 3600

#endif
```

## <a name="link_template_code">⚓</a> Time Initialization template code

This code should be able to be merged into most projects by directly copying a few lines from the sketch. An Internet connection is needed, then the relevant lines are:

```c++
#include <time.h>
#include "secrets.h"

// Time processing information
const char *ntpServer PROGMEM = NTP_SERVER;
const long  utcOffset_sec = UTC_OFFSET_SEC;
const int   daylightOffset_sec = DAYLIGHT_OFFSET_SEC;

configTime(utcOffset_sec, daylightOffset_sec, PSTR(ntpServer));
```

or without PROGMEM

```c++
const char *ntpServer = NTP_SERVER;

configTime(utcOffset_sec, daylightOffset_sec, ntpServer);
```

Make sure to include some delay after `configTime()` before disconnecting from WiFi. It takes a little time to get the time information from the Internet. Calling the supplied `printLocalTime()` is usually enough. Or just `freshLocalTime()`, if you do not want to output the formatted time details. Those are convenience functions for the demonstration. They are not need to actually set the ESP rtc (real time clock) to the time from the Internet. A `struct tm` variable passed in a call to the `getLocalTime()` function from the time library is enough to access the time after it has been set. There are other options as well, but that is beyond the scope of this example, which is focused on getting the time for the esp board set using an [NTP](https://en.wikipedia.org/wiki/Network_Time_Protocol) server.

[View File](https://github.com/mMerlin/esduino/blob/main/set_time_using_ntp/set_time_using_ntp.ino) ¦ [Download](set_time_using_ntp.ino) ¦ [raw](https://raw.githubusercontent.com/mMerlin/esduino/main/set_time_using_ntp/set_time_using_ntp.ino)
