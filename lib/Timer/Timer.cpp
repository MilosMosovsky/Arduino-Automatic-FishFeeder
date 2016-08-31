
#include <Arduino.h>
#include "Timer.h"

int Timer::getDelay() {
  Serial.println(TIMER_DELAY);
  Serial.println("--------------------------------");
  return TIMER_DELAY;
}

Timer::Timer(int delay) {
  TIMER_DELAY = delay;
}

bool Timer::tick() {
  long TIMER_NOW = millis();

  if((TIMER_NOW - TIMER_PREVIOUS) >= TIMER_DELAY) {
    TIMER_PREVIOUS = TIMER_NOW;
    return true;
  }

  return false;
}

void Timer::reset() {
  TIMER_PREVIOUS = millis();
}
