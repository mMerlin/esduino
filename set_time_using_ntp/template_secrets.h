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
