#ifndef LOGMESSAGES_H
#define LOGMESSAGES_H

// NOTE!  Compiler does not enforce any of these!
#define LOG_MESSAGE_TEXT_LEN 80
#define LOG_MESSAGE_LEVEL_LEN 8
#define LOG_MESSAGE_EXTRAS_LEN 6

#define LOG(x) LoggableMsg::log(logMessages::x)

namespace logMessages
{
  // Enumeration of log message levels
  typedef enum
  {
    error = 0,
    warning,
    notice,
    debug,
    
    // Insert all other levels above this line
    levelCnt
  } msgLevel_t;
  
  // C strings (in PROGMEM) to mark the level of each message when it is written to SD card
  const char errorName_p[] PROGMEM = "ERROR";
  const char warningName_p[] PROGMEM = "WARNING";
  const char noticeName_p[] PROGMEM = "NOTICE";
  const char debugName_p[] PROGMEM = "DEBUG";
  
  // Array of the above C strings
  const char* const levelName_p[levelCnt] PROGMEM = 
  {
    errorName_p,
    warningName_p,
    noticeName_p,
    debugName_p
  };
  
  // Enumeration of log message codes
  typedef enum
  {
    realtimeClockNotFound = 0,
    realtimeClockBatteryEmpty,
    sdNotConnected,
    adjustedRtcRelative,
    adjustedRtcAbsolute,
    initializingSdCard,
    successfulSdInitialization,
    sensorStartup,
    foundNewStationName,
    noNewStationName,
    microclimateInfoRetrievalAttempt,
    enteringSleep,
    testError,
    
    // Insert all other codes above this line
    msgIdCnt
  } msgId_t;
  
  // Message C strings (in PROGMEM) to be written to SD card
  const char realtimeClockNotFoundMsg_p[] PROGMEM = "Realtime Clock not found. System has halted, and must be rebooted";
  const char realtimeClockBatteryEmptyMsg_p[] PROGMEM = "Realtime Clock ran out of battery power. Replace the clock battery";
  const char sdNotConnectedMsg_p[] PROGMEM = "No SD Card connected on startup, writing to limited local storage";
  const char adjustedRtcRelativeMsg_p[] PROGMEM = "Set a new time for RTC clock relative to currently set time.";
  const char adjustedRtcAbsoluteMsg_p[] PROGMEM = "Set a new time for RTC clock from scratch. Overwriting the previously set time";
  const char initializingSdCardMsg_p[] PROGMEM = "Initializing SD Card...";
  const char successfulSdInitializationMsg_p[] PROGMEM = "Successfully initializated SD card";
  const char sensorStartupMsg_p[] PROGMEM = "Attempted to initialize system's environment sensor";
  const char foundNewStationNameMsg_p[] PROGMEM = "Found new station name file, saved name to system storage";
  const char noNewStationNameMsg_p[] PROGMEM = "Didn't find a new name for this system";
  const char microclimateInfoRetrievalAttemptMsg_p[] PROGMEM = "Attempted to get current microclimate info from sensor";
  const char enteringSleepMsg_p[] PROGMEM = "Entering sleep";
  const char testErrorMsg_p[] PROGMEM = "Test error";

  typedef struct
  {
    msgLevel_t level;
    const char* text_p;
  } msg_t;

  static const msg_t message_p[msgIdCnt] PROGMEM = 
  {
    {error, realtimeClockNotFoundMsg_p},
    {error, realtimeClockBatteryEmptyMsg_p},
    {warning, sdNotConnectedMsg_p},
    {notice, adjustedRtcRelativeMsg_p},
    {notice, adjustedRtcAbsoluteMsg_p},
    {notice, initializingSdCardMsg_p},
    {notice, successfulSdInitializationMsg_p},
    {notice, sensorStartupMsg_p},
    {notice, foundNewStationNameMsg_p},
    {notice, noNewStationNameMsg_p},
    {notice, microclimateInfoRetrievalAttemptMsg_p},
    {notice, enteringSleepMsg_p},
    {error, testErrorMsg_p},
  };

}

#endif
