/******************************************************************************
This is the main source code file for the microclimate recorder.

Dependencies:
- SHT3X library
- QMP6988 library
- LowPower library
- TimeLib library
- EEPROM library
- Wire library
- SPI library
- SD library
- RTClib and related libraries
- LogTypes
- Loggables
- LogStorageMgrs
******************************************************************************/
#include "defs.h"

// Weather Sensor Libraries
#ifdef ENV_SENSOR_PRESENT
#include "SHT3X.h"
#include "QMP6988.h"
#endif

// Misc. Libraries
#ifdef LOW_POWER_LIBRARY
#include <LowPower.h>
#endif
 #include <TimeLib.h>
#include <Wire.h>
#include <SPI.h>
// #include <jsonlib.h>
#include <SD.h>
// #include <ArduinoJson.h>
#include <EEPROM.h>
#include <avr/power.h>

#include "RTClib.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include "Sleep.h"
#include "Log.h"
#include "LogTypes.h"
#include "Loggables.h"
#include "LogStorageMgrs.h"

#define MAX_TIME_ADJUSTMENT_LEN 25
#define STATION_NAME_EEPROM_OFFSET 0
#define CONFIGURATION_EEPROM_OFFSET 0
#define STATION_NAME_FILENAME F("statOpts/statName.txt")
#define TIME_ADJ_FILENAME F("statOpts/time.txt")
#define SLOW_ARDUINO_CLOCK_SPEED

#define DATA_COLLECTION_PERIOD 5000
#define RTC_SLEEP_SEC 10

#define EEPROM_RESET_PIN 4
#define TEST_ERROR_PIN 5
#define ERROR_INDICATOR_LED_PIN 7
#define OK_TO_REMOVE_SD_INDICATOR_PERIOD 5000
#define OK_TO_REMOVE_SD_INDICATOR_LED_PIN 6
// Slow clock speed
#ifdef SLOW_ARDUINO_CLOCK_SPEED
#define F_CPU 8000000L
#endif

// Initialize global variables and class definitions
#ifdef ENV_SENSOR_PRESENT
SHT3X sht30;  // 13 bytes
QMP6988 qmp6988;  // 126 bytes
#endif

#ifdef SIMULATED_POWER_OFF
bool testWakeup = false;
#endif

RTC_DS3231 *rtc = NULL;  // *rtc is only 2 bytes

bool sdConnected = false;

mdr_t mdr = {0.0, 0.0, 0.0};

LoggableParameters loggableParameters;

bool userInitiatedWake;

bool testErrorOccurred = false;

// Functions

// Interrupt Service Routines
void buttonPressedServiceRoutine()
{
  // userInitiatedWake();
}

void getCurrentWeatherInfo()
{
#ifdef ENV_SENSOR_PRESENT
  mdr.press = qmp6988.calcPressure();
  if (sht30.get() == 0)
  {
    mdr.temp = sht30.fTemp;
    mdr.hum = sht30.humidity;
  }
  else
  {
    mdr.temp = 0, mdr.hum = 0;
  }
#endif
}

void updateRTCTime(const char *timeAdjustment) 
{
#ifndef NEVER //1250 bytes
  int timeAdjustmentAmount;
  byte timeAdjustmentAmountHeader;
  byte index;
  DateTime currentTime, newTime;
  char *timeString;
  char buffer[25] = "MM/DD/YYYY hh:mm:ss";

  if (timeAdjustment[0] == '+' || timeAdjustment[0] == '-') // If it's a relative adjustment
  {
    timeAdjustmentAmount = atoi(timeAdjustment);
    currentTime = rtc->now();
    if (timeAdjustmentAmount > 0) 
    {
      newTime = currentTime + TimeSpan(timeAdjustmentAmount);
    }
    else
    {
      newTime = currentTime - TimeSpan(-timeAdjustmentAmount);
    }
    LOG(adjustedRtcRelative);
  }
  else
  {
    timeString = strchr(timeAdjustment, ' ');
    *timeString = '\0';
    timeString ++;
    //Serial.print(F("Date provided: "));
    //Serial.println(timeAdjustment);
    //Serial.print(F("Time Provided: "));
    //Serial.println(timeString);

    byte mon = atoi(timeAdjustment);
    timeAdjustment = strchr(timeAdjustment, '/') + 1;
    byte day = atoi(timeAdjustment);
    timeAdjustment = strchr(timeAdjustment, '/') + 1;
    int year = atoi(timeAdjustment);

    byte hour = atoi(timeString);
    timeString = strchr(timeString, ':') + 1;
    byte min = atoi(timeString);
    timeString = strchr(timeString, ':') + 1;
    byte sec = atoi(timeString);

    // newTime = DateTime(year, mon, day, hour, min, sec);
    
    DateTime temporary(year, mon, day, hour, min, sec);

    newTime = temporary;

    LOG(adjustedRtcAbsolute);

  }
  rtc->adjust(newTime);

#endif
}

void initializeSdCard()
{
  LOG(initializingSdCard);
// 5601
  if (!SD.begin(10))
  {
    sdConnected = false;
    // If the last known state of the SD card was connected
    if (loggableParameters.getSdConnected())
    {
      // SD card has just been removed, so clear the error flag
      loggableParameters.setErrorFlag(false);
    }
    // LoggableMsg::log(logMessages::sdNotConnected);
    LOG(sdNotConnected);
    // while (1)
    //   ;
  } else
  {
    sdConnected = true;
    LOG(successfulSdInitialization);
  }
  loggableParameters.setSdConnected(sdConnected);
}

void eepromResetIsr()
{
  detachInterrupt(digitalPinToInterrupt(EEPROM_RESET_PIN));
  EepromMgr::getInstance()->resetPushIndices();
}

void testErrorIsr()
{
  detachInterrupt(digitalPinToInterrupt(TEST_ERROR_PIN));
  testErrorOccurred = true;
}

void setup()
{  
#ifndef NEVER // 5649 bytes
  // Declarations
  File timeAdjustmentFile; // 27 bytes
  char timeAdjustmentContents[MAX_TIME_ADJUSTMENT_LEN];
  File stationNameFile;
  char stationName[MAX_STATION_NAME_LEN + 1];

  byte index;
  
#ifdef SLOW_ARDUINO_CLOCK_SPEED
  CPU_CCP = CCP_IOREG_gc;             
  CLKCTRL_MCLKCTRLB = CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm;
/* ... or this here in setup
  _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm);
*/  
  // clock_prescale_set(2);
#endif
  
  pinMode(ERROR_INDICATOR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_INDICATOR_LED_PIN, LOW);
  
  pinMode(OK_TO_REMOVE_SD_INDICATOR_LED_PIN, OUTPUT);
  digitalWrite(OK_TO_REMOVE_SD_INDICATOR_LED_PIN, LOW);
  
  pinMode(EEPROM_RESET_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EEPROM_RESET_PIN), wakeIsr, LOW);
  interrupts();
  pinMode(TEST_ERROR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TEST_ERROR_PIN), testErrorIsr, LOW);

  Serial.begin(9600);
  
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
  
  // delay(5000);
  // Serial.print("mdr.temp: ");
  // Serial.println(mdr.temp);
  // Serial.print("mdr.hum ");
  // Serial.println(mdr.hum);
  // Serial.print("mdr.press ");
  // Serial.println(mdr.press);
  // LoggableMdr lm(&mdr);
  // lm.storeToEeprom();
  // mdr.temp = 12.34;
  // mdr.hum = 56.78;
  // mdr.press = 90.12;
  // lm.storeToEeprom();
  // lm.retrieveFromEeprom();
  // Serial.print("mdr from EEPROM: temp ");
  // Serial.println(ld.GetMdr()->temp);
  // Serial.print("timestamp sec: ");
  // Serial.println(ld.GetTimestamp()->sec);
  // {
  //   LoggableMdr lm(&mdr);
  //   char* record;
  //   for (int i = 0; i < 10; i++)
  //   {
  //     lm.retrieveFromEeprom();
  //     record = lm.getExpandedRecord();
  //     Serial.print("Record ");
  //     Serial.print(i);
  //     Serial.print(": ");
  //     Serial.println(record);
  //   }
  // }
  
#ifdef LOW_POWER_SLEEP
  setupSleep();
#endif
  setupOff();
  
  initializeSdCard();
  
// 3760

  // pinModes
  pinMode(2, INPUT_PULLUP);
  LOG_DEBUG(F("Initialized system wakeup button"));
  
  Wire.begin(); // Wire init, adding the I2C bus.  Wire初始化, 加入i2c总线
#ifdef ENV_SENSOR_PRESENT  
  uint8_t qinit_return = qmp6988.init();
  LOG(sensorStartup);
#endif
  Serial.flush();
// 3642
  if (rtc == NULL) 
  {
    rtc = new RTC_DS3231(); 
  }
// 3532
  if (!rtc->begin())
  {
    LOG(realtimeClockNotFound);
    Serial.flush();
    while (1)
      delay(10);
  }
// 3162

  if (rtc->lostPower())
  {
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    rtc->adjust(DateTime(2022, 1, 21, 15, 0, 0));
    LOG(realtimeClockBatteryEmpty);
  }
// 2672

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  attachInterrupt(digitalPinToInterrupt(2), buttonPressedServiceRoutine, FALLING);
  LOG_DEBUG(F("Finalized initial system wakeup button setup"));

  timeAdjustmentFile = SD.open(TIME_ADJ_FILENAME);
  //Serial.println(F("Opened time adjustment file"));
// 2450

  if (timeAdjustmentFile)
  {
    while (timeAdjustmentFile.available())
    {
      if (index < MAX_TIME_ADJUSTMENT_LEN - 1)
      {
        timeAdjustmentContents[index++] = (char)(timeAdjustmentFile.read());
      } else
      {
        break;
      }
    }
    timeAdjustmentContents[index] = '\0';
    Serial.println(F("Updating RTC Time"));
    updateRTCTime(timeAdjustmentContents);  
    SD.remove(TIME_ADJ_FILENAME);
    index = 0;
  }
  //Serial.println(F("Read time adjustment file"));
  
  DateTime current = rtc->now();
  setTime(current.hour(), current.minute(), current.second(),
    current.day(), current.month(), current.year());
    
// 472

  stationNameFile = SD.open(STATION_NAME_FILENAME);
  if (stationNameFile)
  {
    while (stationNameFile.available())
    {
      if (index < MAX_STATION_NAME_LEN - 1)
      {
        stationName[index++] = (char)(stationNameFile.read());
      }
      else
      {
        break;
      }
    }
    stationName[index] = '\0';
    index = 0;
    // To avoid wear on the EEPROM, commented this out until it checks for new name
    loggableParameters.setStationName(stationName);
    // setStationNameInEeprom();
    stationNameFile.close();
    SD.remove(STATION_NAME_FILENAME);
    LOG(foundNewStationName);
  }
  else
  {
    LOG(noNewStationName);
  }
  // Serial.println(stationNameContents);
#endif

  userInitiatedWake = !rtc->alarmFired(1);
}

void loop()
{
#ifndef NEVER // 2526 bytes
  File weatherValuesFile;
  bool fileIsEmpty;
  DateTime wakeTime;
  static bool alreadyMovedMdrs = false;

  DateTime time = rtc->now();
  
  if (testErrorOccurred)
  {
    LoggableMsg::log(logMessages::testError);
    LOG(testError);
    testErrorOccurred = false;
  }
  
  attachInterrupt(digitalPinToInterrupt(TEST_ERROR_PIN), testErrorIsr, LOW);
#ifdef SIMULATED_POWER_OFF
  userInitiatedWake = !rtc->alarmFired(1);
  initializeSdCard();
#endif

  if (userInitiatedWake && loggableParameters.getErrorFlag())
  {
    // Serial.println("Trying to light error LED");
    digitalWrite(ERROR_INDICATOR_LED_PIN, HIGH);
  }

  if (sdConnected && !alreadyMovedMdrs)
  {
    moveAllFromEepromToSd();
    alreadyMovedMdrs = true;
  }
  
  if (userInitiatedWake)
  {
    SdMgr* mgr = SdMgr::getInstance();
    mgr->pushTimeNow();
    
    digitalWrite(OK_TO_REMOVE_SD_INDICATOR_LED_PIN, HIGH);
    delay(OK_TO_REMOVE_SD_INDICATOR_PERIOD);
    digitalWrite(OK_TO_REMOVE_SD_INDICATOR_LED_PIN, LOW);
    // If SD card has been removed
    if (sdConnected && !SD.begin(10))
    {
      loggableParameters.setErrorFlag(false);
      digitalWrite(ERROR_INDICATOR_LED_PIN, LOW);
    }
  }
  else
  {
      //Run Setup Functions
      getCurrentWeatherInfo();
      LOG(microclimateInfoRetrievalAttempt);

      LoggableMdr lm(&mdr);
      lm.store();
  }
  
#ifdef LOW_POWER_SLEEP
  time = rtc->now();
  wakeTime = time + TimeSpan(RTC_SLEEP_SEC);  
  // Serial.print(F("Will wake at "));
  // Serial.print(wakeTime.hour());
  // Serial.print(":");
  // Serial.print(wakeTime.minute());
  // Serial.print(":");
  // Serial.println(wakeTime.second());
  // Serial.flush();
  LOG(enteringSleep);
  sleepUntil(wakeTime);
// #else
//   Serial.print(F("Delaying for msec "));
//   Serial.println(DATA_COLLECTION_PERIOD);
//   delay(DATA_COLLECTION_PERIOD);
//   Serial.println(F("Done delaying")); 
#endif
  TurnOff();
  
#ifdef SIMULATED_POWER_OFF
  digitalWrite(ERROR_INDICATOR_LED_PIN, LOW);
  int i = 0;
  while (!testWakeup)
  {
    // i++;    
    delay(1000);
    Serial.println("Waiting ...");
  }
  testWakeup = false;
#endif
 
//  delay(DATA_COLLECTION_PERIOD);
#endif
}
