#include "Log.h"
#include "RTClib.h"
#include "Loggables.h"

extern RTC_DS3231 *rtc;
extern LoggableParameters loggableParameters;

char flashStringHelper[FLASH_STRING_HELPER_LEN+1];

void createErrorLogEntry(int logTypeId, const char *logMessage, File logFile)
{
  char timeString[20] = "MM/DD/YYYY hh:mm:ss";
  
  logFile.print('[');
  // If the global rtc object has been created
  if (rtc)
  { 
    DateTime timeNow = rtc->now();

    logFile.print(timeNow.toString(timeString));
  } else
  {
    logFile.print(millis());
    logFile.print(" msec since startup");
  }
  logFile.print("], ");
  
  if (logTypeId == 1)
  {
    loggableParameters.setErrorFlag(true);
    logFile.print("ERROR");
  } else if (logTypeId == 2)
  {
    logFile.print("WARNING");
  } else if (logTypeId == 3)
  {
    logFile.print("Notice");
  }
  logFile.print(": ");
  logFile.println(logMessage);
}

void logToSD(int logTypeId, const __FlashStringHelper *logMessage)
{
  strncpy_P(flashStringHelper, (const char*)logMessage, FLASH_STRING_HELPER_LEN);
  logToSD(logTypeId, flashStringHelper);  
}

void logToSD(int logTypeId, const char *logMessage)
{
  // Serial.println("In logToSD(int logTypeId, const char *logMessage)");
  // Serial.flush();
  File logFile = SD.open(ERROR_LOG_FILENAME, FILE_WRITE);

  if ((logFile) && (logTypeId <= LOG_LEVEL))
  { 
    createErrorLogEntry(logTypeId, logMessage, logFile);
    logFile.close();
  }
#ifdef PRINT_LOG_MESSAGES_TO_SERIAL  
  Serial.println(logMessage);
  Serial.flush();
#endif
}
