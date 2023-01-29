/******************************************************************************
This module contains functions and data related to putting the whole
microclimate recorder - both microcontrollers and peripherals - into and out
of low power mode.

Dependencies:
- LowPower library
- Realtime clock libraries and global variable rtc
- SD card library
******************************************************************************/
#include <Arduino.h>
#include "defs.h"
#include "Sleep.h"
#ifdef LOW_POWER_LIBRARY
#include "LowPower.h"
#endif

#include "RTClib.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <SD.h>

// This pin powers the SD card reader
#define SD_CARD_PWR_PIN 6
// This pin powers the ENV III sensor
#define ENV_SENSOR_PWR_PIN 8
// This pin is attached to the wake up signal from the RTC
#define WAKE_PIN 3
// This pin signals to the power timer to turn off power
#define DONE_PIN 9

#ifdef SIMULATED_POWER_OFF
#define SIM_POWER_ON_PIN 8
extern bool testWakeup;
#endif

/*
Interrupt service routine for the wake up signal from the RTC
*/
void wakeIsr()
{
  detachInterrupt(digitalPinToInterrupt(WAKE_PIN));
  // power on the env sensor
//  digitalWrite(ENV_SENSOR_PWR_PIN, HIGH);
  digitalWrite(SD_CARD_PWR_PIN, HIGH);
  SD.begin(10);
}

/*
Initializes everything needed later to go into low power mode
*/
void setupSleep()
{
  pinMode(ENV_SENSOR_PWR_PIN, OUTPUT);
  pinMode(SD_CARD_PWR_PIN, OUTPUT);
  digitalWrite(ENV_SENSOR_PWR_PIN, HIGH);
  digitalWrite(SD_CARD_PWR_PIN, HIGH);
// Does the SD card reader need time to start up?
  delay(2000);
  interrupts();
  pinMode(WAKE_PIN, INPUT_PULLUP);
}

#ifdef SIMULATED_POWER_OFF
void testPowerOnIsr()
{
  detachInterrupt(digitalPinToInterrupt(SIM_POWER_ON_PIN));
  testWakeup = true;
  // Serial.println("In testPowerOnIsr");
}
#endif

void setupOff()
{
  pinMode(DONE_PIN, OUTPUT);
  digitalWrite(DONE_PIN, LOW);
#ifdef SIMULATED_POWER_OFF
  pinMode(SIM_POWER_ON_PIN, INPUT_PULLUP);
  interrupts();
#endif
}

/*
Go into low-power mode until the given time
After waking up, resume full operation
*/
void sleepUntil(const DateTime &dt)
{
#ifndef NEVER
  rtc->disable32K();
  rtc->clearAlarm(1);
  rtc->clearAlarm(2);
  rtc->disableAlarm(2);
  rtc->writeSqwPinMode(DS3231_OFF);
  if (rtc->setAlarm1(dt, DS3231_A1_Second))
  {
    Serial.println(F("Alarm was set"));
  } else {
    Serial.println(F("Alarm was not set"));
  }

  /*  
  delete rtc;
  rtc = NULL;
  */
  
  /*  
  // send stop condition to serial
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

  // wait for stop condition to be exectued on bus
  // TWINT is not set after a stop condition!
  while(TWCR & _BV(TWSTO)){
    continue;
  }
  */

  Wire.end();

  // power off the env sensor
//  digitalWrite(ENV_SENSOR_PWR_PIN, LOW);
//power off the SD card reader
  digitalWrite(SD_CARD_PWR_PIN, LOW);
  Serial.flush();
  
  attachInterrupt(digitalPinToInterrupt(WAKE_PIN), wakeIsr, LOW);
#ifdef LOW_POWER_LIBRARY  
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  
#endif

  Serial.println("AWAKE!");
// Doesn't seem to be declared for nano every
#ifndef NANO_EVERY
  TWCR = 0;
#endif
  Wire.begin();
//  delay(1000);
//  if (rtc == NULL) rtc = new RTC_DS3231;
  rtc->begin();
#endif
}

long getSecondsSinceMidnight(DateTime time)
{
  long secondsSinceMidnight = 0;
  
  secondsSinceMidnight += (long)(time.hour()) * 3600;
  secondsSinceMidnight += time.minute() * 60;
  secondsSinceMidnight += time.second();

  return secondsSinceMidnight;
}

// int secondsSinceMidnightToDateTime(int secondsSinceMidnight, DateTime dateReference)
// {
//   int hours;
//   int minutes;
//   int seconds;
//   int remainingTime;

//   hours = secondsSinceMidnight / 3600;
//   remainingTime = secondsSinceMidnight - (hours * 3600);
//   minutes = remainingTime / 60;
//   remainingTime -= (minutes * 60);
//   seconds = remainingTime;

//   // DateTime newDateTime(dateReference.year(), dateReference.month());
//   // newDateTime()
//   // newDateTime.second() = seconds;
//   // newDateTime.minute() = minutes;
//   // newDateTime.hour() = hours;
//   // newDateTime.day() = dateReference.day();
//   // newDateTime.month() = dateReference.month();
//   // newDateTime.year() = dateReference.year();
// }

void TurnOff()
{
  int collectionPeriodNumber;
  DateTime nextDataCollectionPeriod;
  DateTime timeNow = rtc->now();
  long alarmTimeSecondsPastMidnight;
  long secondsSinceMidnight;

  secondsSinceMidnight = getSecondsSinceMidnight(timeNow);
  collectionPeriodNumber = secondsSinceMidnight / (int)DATA_COLLECTION_PERIOD_SEC;
  // nextDataCollectionPeriod = rtc->now();
  alarmTimeSecondsPastMidnight = (long)(collectionPeriodNumber + 1) * DATA_COLLECTION_PERIOD_SEC;

  TimeSpan timeToNextCollectionPeriod(alarmTimeSecondsPastMidnight - secondsSinceMidnight);

  // nextDataCollectionPeriod = secondsSinceMidnightToDateTime((collectionPeriodNumber + 1) * DATA_COLLECTION_PERIOD_SEC, nextDataCollectionPeriod);
  nextDataCollectionPeriod = timeNow + timeToNextCollectionPeriod;
  
  char buffer[25];
  Serial.print("Current time: ");
  strcpy(buffer, "MM/DD/YYYY hh:mm:ss");
  timeNow.toString(buffer);
  Serial.println(buffer);
 
  Serial.print("Next collection time: ");
  strcpy(buffer, "MM/DD/YYYY hh:mm:ss");
  nextDataCollectionPeriod.toString(buffer);
  Serial.println(buffer);
 
  rtc->clearAlarm(1);
  rtc->writeSqwPinMode(DS3231_OFF);
  rtc->setAlarm1(nextDataCollectionPeriod, DS3231_A1_Hour); 
  Serial.println("Powering off");
  Serial.flush();
  
  digitalWrite(DONE_PIN, HIGH);
#ifdef SIMULATED_POWER_OFF
  attachInterrupt(digitalPinToInterrupt(SIM_POWER_ON_PIN), testPowerOnIsr, LOW);
  pinMode(WAKE_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WAKE_PIN), wakeIsr, LOW);
#endif
}