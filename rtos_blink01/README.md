# RTOS Blink 01

* [esduino](https://mmerlin.github.io/esduino/) github.io pages.

* Features
  * Example showing basic conversion of an Arduino sketch to a task

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

This example does not use any external libraries. All of the needed functionality is included when ESP32 boards are added to the Arduino environment. This first example keeps the code as close as practical to the basic Arduino "Blink" sketch, as modified for WCRS ARDX programming. Looking at the code shows that it contains 3 separate copies of `void setup()` and `void loop()` code, each changed slightly to match the LED pin number and delay times for that copy. The "main" `void loop()` is empty, and `void setup()` simply starts tasks that run the individual setup and loop functions, using the same structure as a normal (non-RTOS) sketch would.

Many sketches can be implements as a task using this structure. As long as they do not simultaneously require the same resources, multiple tasks, from multiple converted sketches, can be combined into a single sketch. There are many additional freeRTOS specific functions available to make the tasks share the resources better. They can explicitly `yield` to other running tasks when they do not need to be active for awhile. For example, there is an rtos version of the delay command that puts the task to sleep for the specified time, instead waiting. That turns the blinking into very 'light' code. It would use barely any processor time, leaving almost all of it available to some other task that actually needed CPU cycles for its job.

The stack size value used for the demonstration tasks was a general, conservative value taken from other example code. That can be adjusted up or down to match the needs of the individual tasks. In testing, I got blink to work with 575 words. At 550, the tasks froze.

[View File](https://github.com/mMerlin/esduino/blob/main/rtos_blink01/rtos_blink01.ino) ¦ [Download](rtos_blink01.ino) ¦ [raw](https://raw.githubusercontent.com/mMerlin/esduino/main/rtos_blink01/rtos_blink01.ino)
