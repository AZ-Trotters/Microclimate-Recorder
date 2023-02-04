#ifndef LOGGABLES_H
#define LOGGABLES_H

#include "LogTypes.h"
#include "LogStorageMgrs.h"
#include "LogMessages.h"

#define PRINT_LOG_MESSAGES_TO_SERIAL

uint8_t moveAllFromEepromToSd();

class Loggable
{
  public:
};

class LoggableParameters : public Loggable
{
  public:
  
  LoggableParameters();
  ~LoggableParameters();
  
  uint8_t retrieveFromEeprom();
  uint8_t storeToEeprom();
  uint8_t checkStationName();
  uint8_t setErrorFlag(const bool flag);
  bool getErrorFlag();
  uint8_t setSdConnected(const bool sdConnected);
  bool getSdConnected();
  uint8_t setStationName(const char* name);
  const char* getStationName();
  
  private:
  
  uint8_t compress();
  
  bool initialized_;
  persistentParameters_t parameters_;
  logBlob_t blob_;
};

class LoggableMdr : public Loggable
{
  public:
  
  LoggableMdr(const mdr_t* mdrPtr = NULL, const LogTimestamp* timestampPtr = NULL);
  ~LoggableMdr();
  
  uint8_t store();
  uint8_t storeToSd();
  uint8_t storeToEeprom();
  uint8_t retrieveFromEeprom();
  mdr_t* getMdr();
  const char* getExpandedRecord();
  
  const static uint8_t expandedSize = 60; // size in bytes of the blob returned by getExpanded()

  private:
 
  uint8_t compress();
  uint8_t uncompress();
  uint8_t expand();
 
  mdr_t* mdr_;
  LogTimestamp* timestamp_;
  char* stampedRecord_;
  logBlob_t mdrBlob_;
};


class LoggableMsg : public Loggable
{
  public:
  
  LoggableMsg(const logMessages::msgId_t msgId, const LogTimestamp* timestampPtr = NULL);
  ~LoggableMsg();
  
  static uint8_t log(const logMessages::msgId_t msgId);
  uint8_t store();
  uint8_t storeToSd();
  uint8_t storeToEeprom();
  uint8_t retrieveFromEeprom();
  
  const static uint8_t expandedSize = LogTimestamp::expandedSize + LOG_MESSAGE_TEXT_LEN + LOG_MESSAGE_LEVEL_LEN + LOG_MESSAGE_EXTRAS_LEN; // maximum size when expanded

  private:
 
  uint8_t compress();
  uint8_t uncompress();
 
  compressedLogCode code_;
  LogTimestamp* timestamp_;
  char* expandedMsg_;
  logMessages::msg_t localMsg_;

};



#endif