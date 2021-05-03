/*
  rtos_blink02.ino

Create multiple tasks, each of which uses the typical blink code. As tasks,
they do not block each other, despite the use of `delay()`.

This reuses the blink task code by passing pin numbers and delay times to the
created tasks, then to the almost standard taskLoop function. There are 3
tasks, but only a single initialization and loop function.

Delay values choosen to make sure the cycle lengths are NOT synchronized. The
cycle lengths (on + off times) are 400, 900, 1300 milliseconds, none of which
are simple multiples.

This sketch works for demonstration purposes, but there are better methods to
use from freeRTOS to manage the tasks.
*/

struct task_data_t {
  size_t ledPin;
  unsigned long onTime;
  unsigned long offTime;
};

const task_data_t taskData[] = {
  {14, 100, 300},
  {32, 300, 600},
  {15, 500, 800}
};
const size_t taskCount = sizeof(taskData) / sizeof(taskData[0]);
String taskNames[taskCount];

void setup() {
  // Initialize the pins to use with the LEDs before starting the tasks,
  // instead of inside a setup for the task
  for (size_t i = 0; i < taskCount; i++) {
    pinMode(taskData[i].ledPin, OUTPUT);
    taskNames[i] = "Blink " + i; // A unique generated value
  }

  // create a separate task to blink each LED
  for (size_t i = 0; i < taskCount; i++) {
    xTaskCreate(
      taskBlink,        /* Task function. */
      taskNames[i].c_str(), /* String with name of task. */
      10000,            /* Stack size in words. */
      (void *)&taskData[i], /* Parameter passed as input of the task */
      1,                /* Priority of the task. */
      NULL);            /* Task handle. */
  }
}

void loop() {
  // Nothing being done here in this example
}

/**
 * function to be run as a task to blink a single LED
 *
 * @param[in] parameter data about the led pin blink timing
 */
void taskBlink(void * parameter)
{
  task_data_t * blinkData = (task_data_t *)parameter;
  while (true) // Runs forever, link void loop()
  {
    taskLoop(blinkData->ledPin, blinkData->onTime, blinkData->offTime);
  }
}

/**
 * void loop() clone, passing in the data needed for blink
 */
void taskLoop(size_t blinkPin, unsigned long onDelay, unsigned long offDelay)
{
  digitalWrite(blinkPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(onDelay);                 // wait while the LED stays on
  digitalWrite(blinkPin, LOW);    // turn the LED off by making the voltage LOW
  delay(offDelay);                // wait while the LED stays off
}
