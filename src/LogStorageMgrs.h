#ifndef LOGSTORAGEMGRS_H
#define LOGSTORAGEMGRS_H

#include "LogTypes.h"
#include <SD.h>

#define WEATHER_DATA_FILENAME F("statInfo/wthrvals.csv")
#define TIMESTAMP_FILENAME F("statInfo/btntime.txt")
#define ERROR_LOG_FILENAME F("statInfo/errorlog.txt")

typedef uint8_t compressedLogCode;

class LogStorageMgr
{
  public:
  
  typedef enum {
    sd,
    eeprom,
  }cache_t;
};

class EepromMgr : public LogStorageMgr
{
  public:
  
  static EepromMgr * getInstance();
  uint8_t pullParameters(logBlob_t* blob);
  uint8_t pushParameters(logBlob_t* blob);

  uint8_t pushMdr(const logBlob_t* timestampBlob, const logBlob_t* mdrBlob);
  uint8_t pullMdr(logBlob_t* timestampBlob, logBlob_t* mdrBlob);
  
  uint8_t pushMsg(logBlob_t *timestampBlob, compressedLogCode code);
  uint8_t pullMsg(logBlob_t *timestampBlob, compressedLogCode* code);
  uint8_t resetPushIndices();
  
  private:
  // Only this class can instantiate itself
  EepromMgr();
  
  // Don't allow cloning or assigning
  EepromMgr(EepromMgr& other);
  void operator = (const EepromMgr &);
  
  static EepromMgr* instance_;
  unsigned char mdrCnt_;
  unsigned char mdrPushIndex_;
  unsigned char mdrPullIndex_;
  unsigned char msgCnt_;
  unsigned char msgPushIndex_;
  unsigned char msgPullIndex_;
};

class SdMgr : public LogStorageMgr
{
  public:
  
  static SdMgr * getInstance();
  uint8_t pushMdr(const char* record);
  uint8_t pushTimeNow();
  
  uint8_t pushMsg(const char* content);
  uint8_t pushMsg(const __FlashStringHelper* content);
  
  private:
  
  // Only this class can instantiate itself
  SdMgr();
  
  // Don't allow cloning or assigning
  SdMgr(SdMgr& other);
  void operator = (const SdMgr &);
  
  int8_t openFile(__FlashStringHelper* fileName, File& file);
  uint8_t createWeatherValueDefaultHeaders();
  uint8_t createNeededSdDirectories();

  
  static SdMgr* instance_;
  File mdrFile_;
  File msgFile_;
};


#endif