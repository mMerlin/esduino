# Just Connect to WiFi AP

* Features
  * WiFi AP credentials read from [`secrets.h` include file](#link_secrets).
    * [.gitignore](#link_git_ignore)
    * [include guard](#link_include_guard)
    * [Template include file](#link_template_secrets) to copy to create personal version of `secrets.h`
  * [Template code](#link_template_code) to establish connection to WiFi Access Point
  * ESP32 or ESP8266 board
    * Once provided credentials to access a local access point, this code should work with any ESP32 or ESP8266 board that matches the `board` selections available in Arduino IDE.

This sketch can be used to provide template wireless access point connection code for use in other projects. It can also be built as a standalone project to establish a connection to an access point that will be remembered across resets, power cycling, and new sketch loads. Once successfully connected, the WiFi module stores the needed information in flash memory. Other sketches can then use that to "re"-connect to the same AP, without supplying any login credentials. See
[no_credentials_reconnect](../no_credentials_reconnect/)
for example and template code for reconnecting.

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

## <a name="link_secrets">⚓</a> Credentials in `secrets.h`

This sketch demonstrates connecting to a local WiFi access point using SSID and password credentials from a `secrets.h` include file.

Many examples (for code simplicity) have the wireless AP (Access Point) SSID and password hard-coded in the sketch. Either as definitions or constants at the top, or directly in the function call parameters. Doing things that way is not 'safe', if the resulting project is to be shared with others, that are not part of the local project team.

One way to avoid this, is to move the hard-code values into a `secrets.h` file that is included by the sketch. The `secrets.h` file then needs to be excluded when sharing the project. When sharing use a git (github and other) repository, that can be done automatically, by adding a [.gitignore](#link_git_ignore) file to the project, before any additions are done after the `secrets.h` file has been created.

Since the `secrets.h` file, and the definitions it provides, are still needed to use the project, a [Template include file](#link_template_secrets) and instructions should be provided with the project.

### <a name="link_git_ignore">⚓</a> .gitignore file

Specifying the access credentials in the `secrets.h` file is not enough to keep them private, if the secrets file is included in a repository that is shared publicly. To prevent that `leakage`, a `.gitignore` file can be added to the git repository that marks the `secrets.h` file to be excluded from `add` operations. As long as the `.gitignore` file, with the proper entry, exists before adding new files (after creating secrets.h), git will not offer to automatically save the secrets.h file in the repository. It remains in the local project folder, but is not part of the published repository.

[View File](https://github.com/mMerlin/esduino/blob/main/.gitignore) ¦ [Download](https://raw.githubusercontent.com/mMerlin/esduino/main/.gitignore) (right-click + Save As)

```.gitignore
# Not to be shared with the project files
secrets.h
```

When using git to share the project, a `.gitignore` file can be included, with an entry to exclude the `secrets.h` file. Since people trying to use the shared project will need their own secrets file, include a `secrets_template.h` file in the project, that contains samples of the needed information, and instructions for copying it to `secrets.h`, and making the needed changes there.

### <a name="link_include_guard">⚓</a> include guard

An [include guard](https://en.wikipedia.org/wiki/Include_guard) is a safety measure, used to prevent a file from being included in a project build multiple times. For the typical usage of include (.h) files, including it once will provide all of the needed information for a single build (compile). Additional inclusions can cause problems, due to duplicate names.

```c++
#ifndef UNIQUE_NAME_FILE_H
#define UNIQUE_NAME_FILE_H

// Normal include file content

#endif
```

The initial `#ifndef` line checks if the unique name has already been defined. If it does exist, everything up to the corresponding `#endif` is skipped. The `#define` line creates the unique name, so the wrapped *normal* content will only be processed (included) the first time the compiler reads the file.

A project with a single .ino file and single .h file does not require this. Adding more .h and .cpp files to the project often results in the same .h file(s) being included from multiple places. There is no problem with using an include guard when it not needed. The compiler will still process the content exactly once. It is a good habit to provided the guard, so that it will exist when it is needed.

### <a name="link_template_secrets">⚓</a> template for secrets.h

Since the `secrets.h` file is excluded from shared projects, to hide personal information, a way for other project users to easily create their own version is needed. One way to do that is to provided a template file containing dummy values that need to be replaced. Additional instructions can be provided different places.

* The project README can include project setup instructions
* The template file can include comments about how to use it
* The (main) project code file can include comments with the steps needed to create `secrets.h` from the template file

[View File](https://github.com/mMerlin/esduino/blob/main/just_connect_wifi_ap/template_secries.h) ¦ [Download](template_secries.h)

```c++
#ifndef MY_SECRETS_H
#define MY_SECRETS_H

// Copy this file to `secrets.h` in the project folder, and replace the dummy
// defined values with those needed for your environment. Do not edit this
// (the template) file. Copy it, then edit the copy. This block
// of comments can optionally be removed from the resulting `secrets.h` file.

#define WIFI_SSID "your_access_point_name"
#define WIFI_PASSWORD "password_for_your_ap"

#endif
```

## <a name="link_template_code">⚓</a> WiFi connection template code

This code should be able to be merged into most projects by directly copying the `attemptConnection()` and `reportConnectionDetails()` functions. A connection is created by calling `attemptConnection()` (typically in `setup()`, but other options work too), and passing the required credential information. Including the `secrets.h` file will provide access to argument names specified in the example code.
