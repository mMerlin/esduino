/*
  rtos_blink01.ino

Create multiple tasks, each of which uses the typical blink code. As tasks,
they do not block each other, despite the use of `delay()`.

This duplicates the very similar individual task and loop code, to keep the
code as similar as practical to the standard (WCRS version) Arduino single LED
blink sketch.

Delay values choosen to make sure the cycle lengths are NOT synchronized. The
cycle lengths (on + off times) are 400, 900, 1300 milliseconds, none of which
are simple multiples.

This sketch works for demonstration purposes, but there are better methods to
use from freeRTOS to manage the tasks.
*/

const unsigned int TASK1_PIN = 14;
const unsigned long TASK1_ON_TIME = 1000;
const unsigned long TASK1_OFF_TIME = 300;
const unsigned int TASK2_PIN = 32;
const unsigned long TASK2_ON_TIME = 300;
const unsigned long TASK2_OFF_TIME = 600;
const unsigned int TASK3_PIN = 15;
const unsigned long TASK3_ON_TIME = 500;
const unsigned long TASK3_OFF_TIME = 800;

void setup() {
  // create a separate task to blink each LED

  xTaskCreate(
    task1Main,        /* Task function. */
    "blink 1",        /* String with name of task. */
    10000,            /* Stack size in words. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
  xTaskCreate(
    task2Main,        /* Task function. */
    "blink 2",        /* String with name of task. */
    10000,            /* Stack size in words. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
  xTaskCreate(
    task3Main,        /* Task function. */
    "blink 3",        /* String with name of task. */
    10000,            /* Stack size in words. */
    NULL,             /* Parameter passed as input of the task */
    1,                /* Priority of the task. */
    NULL);            /* Task handle. */
}

void loop() {
  // Nothing being done here in this example
}

// Task 1 functions

/**
 * Emulate the wrapper of a standalone Arduino Sketch
 *
 * @param[in] parameter data passed to the task on startup: unused here
 */
void task1Main(void * parameter)
{
  task1Setup();
  while(true) { // forever
    task1Loop();
  }
}

/**
 * Emulate the setup() function of a standalone Arduino Sketch
 *
 * This could be done in the main sketch setup() function, but is split out for
 * demonstration, and to make the task code look more like a regular sketch.
 */
void task1Setup()
{
  // Initialize the pin to use with the LED
  pinMode(TASK1_PIN, OUTPUT);
}

/**
 * Emulate the loop() function of a standalone Arduino Sketch
 */
void task1Loop()
{
  digitalWrite(TASK1_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(TASK1_ON_TIME);           // wait while the LED stays on
  digitalWrite(TASK1_PIN, LOW);   // turn the LED off by making the voltage LOW
  delay(TASK1_OFF_TIME);          // wait while the LED stays off
}

// Task 2 functions

/**
 * Emulate the wrapper of a standalone Arduino Sketch
 *
 * @param[in] parameter data passed to the task on startup: unused here
 */
void task2Main(void * parameter)
{
  task2Setup();
  while(true) { // forever
    task2Loop();
  }
}

/**
 * Emulate the setup() function of a standalone Arduino Sketch
 *
 * This could be done in the main sketch setup() function, but is split out for
 * demonstration, and to make the task code look more like a regular sketch.
 */
void task2Setup()
{
  // Initialize the pin to use with the LED
  pinMode(TASK2_PIN, OUTPUT);
}

/**
 * Emulate the loop() function of a standalone Arduino Sketch
 */
void task2Loop()
{
  digitalWrite(TASK2_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(TASK2_ON_TIME);           // wait while the LED stays on
  digitalWrite(TASK2_PIN, LOW);   // turn the LED off by making the voltage LOW
  delay(TASK2_OFF_TIME);          // wait while the LED stays off
}

// Task 3 functions

/**
 * Emulate the wrapper of a standalone Arduino Sketch
 *
 * @param[in] parameter data passed to the task on startup: unused here
 */
void task3Main(void * parameter)
{
  task3Setup();
  while(true) { // forever
    task3Loop();
  }
}

/**
 * Emulate the setup() function of a standalone Arduino Sketch
 *
 * This could be done in the main sketch setup() function, but is split out for
 * demonstration, and to make the task code look more like a regular sketch.
 */
void task3Setup()
{
  // Initialize the pin to use with the LED
  pinMode(TASK3_PIN, OUTPUT);
}

/**
 * Emulate the loop() function of a standalone Arduino Sketch
 */
void task3Loop()
{
  digitalWrite(TASK3_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(TASK3_ON_TIME);           // wait while the LED stays on
  digitalWrite(TASK3_PIN, LOW);   // turn the LED off by making the voltage LOW
  delay(TASK3_OFF_TIME);          // wait while the LED stays off
}
