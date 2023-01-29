#ifndef SLEEP_H
#define SLEEP_H
#include "RTClib.h"

#define DATA_COLLECTION_PERIOD_SEC 10

void wakeIsr();
void setupSleep();
void sleepUntil(const DateTime &dt);

void testPowerOnIsr();
void setupOff();
void TurnOff();

extern RTC_DS3231 *rtc;

#endif