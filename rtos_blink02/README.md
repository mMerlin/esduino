# RTOS Blink 02

* [esduino](https://mmerlin.github.io/esduino/) github.io pages.

* Features
  * Example showing passing data to tasks, allowing code to be reused
  * refactor of [rtos_blink01](../rtos_blink01/) code

<!--
* [Link](#link_link)
## <a name="link_link">⚓</a> Link
-->

This example does not use any external libraries. All of the needed functionality is included when ESP32 boards are added to the Arduino environment. This second example refactors the [rtos_blink01](../rtos_blink01/) code to remove duplication. It passes data to the generic code to provide the values needed to get the same result.

The task creation method used accepts a single generic (void) pointer. To pass the multiple values needed, they are gathered into a `struct` type variable, the address of which is passed to the task when it is created. A different structure for each created task.

The `void loop()` equivalent section of the code is still being kept the same as a basic Arduino "Blink" sketch, just passing in the values as parameters, instead of using global variables. With something this simple, `taskBlink()` and `taskLoop()` could easily be combined into a single function. They are left separate to keep the structure cleaner. It also shows how little change is needed to implement a «simple» sketch as a task. Just add a wrapper function to execute the renamed `void loop()`. The renamed function has parameters that match the global variable names of the original sketch. More work (but not a lot) would be needed if loop was updating those `global` values.

[View File](https://github.com/mMerlin/esduino/blob/main/rtos_blink02/rtos_blink02.ino) ¦ [Download](rtos_blink02.ino) ¦ [raw](https://raw.githubusercontent.com/mMerlin/esduino/main/rtos_blink02/rtos_blink02.ino)
