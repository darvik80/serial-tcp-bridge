#include "profile.h"

#include <Arduino.h>

#include "Scheduler.h"

uint64_t lastTime = 0;

Scheduler scheduler;

void test5000() {
    Serial.write("Test 5000\r\n");
}

void test10000() {
    Serial.write("Test 10000\r\n");
}

void setup() {
    // write your initialization code here
    Serial.begin(57600);
    while (!Serial) { }


    scheduler.scheduleFixedDelay((uint64_t)5000, &test5000);
    scheduler.scheduleFixedRate((uint64_t)10000, &test10000);
    scheduler.setup();
}

void loop() {
    scheduler.loop();
}