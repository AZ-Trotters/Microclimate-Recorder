/******************************************************************************
This module contains classes to manage data to be logged, for instance to the 
SD card or to EEPROM.
These classes are responsible for:
- converting these data when needed among three formats:
  - native format, the default format, used to access individual fields
  - compressed format (for storage on EEPROM)
  - expanded format for easy human reading
- coordinating storage and retrieval with the right LogStorageMgrs

Dependencies:
- LogTypes
- LogStorageMgrs
******************************************************************************/
#include "Loggables.h"
#include "defs.h"
#include "LogTypes.h"

extern bool sdConnected;
extern mdr_t mdr;
extern persistentParameters_t persistentParameters;
extern LoggableParameters loggableParameters;

void printParameters(const persistentParameters_t* parameters)
{
  Serial.print("station name: ");
  Serial.println(parameters->stationName);
  
  Serial.print("error flag: ");
  Serial.println((int)(parameters->errorFlag));
}

uint8_t moveAllFromEepromToSd()
{
  Serial.println("In moveAllFromEepromToSd");
  
  // Allocate a local time struct and timestamp object to use for all transfers
  logTime_t time = {01, 01, 1970, 0, 0, 0};
  LogTimestamp timestamp(&time);
  if (!sdConnected)
    return -1;

  // Braces to create a block of code so that the LoggableMdr will go out of scope after is is used
  {
    // Use the global mdr (no danger of contention)
    // Use the locally declared timestamp to avoid contention with any logged errors
    // that might occur during this move
    LoggableMdr loggableMdr(NULL, &timestamp);
    
    // While there are still mdrs to retrieve
    while(loggableMdr.retrieveFromEeprom() != 1)
    // while(false)
    {
      // Serial.println("Moving a record from EEPROM to SD");
      loggableMdr.storeToSd();
    }
  }
  
  // Braces to create a block of code so that the LoggableMsg will go out of scope after is is used
  {
    // Use the locally declared timestamp to avoid contention with any logged errors
    // that might occur during this move
    LoggableMsg loggableMsg(logMessages::msgIdCnt, &timestamp);
    
    // While there are still mdrs to retrieve
    while(loggableMsg.retrieveFromEeprom() != 1)
    // while(false)
    {
      // Serial.println("Moving a record from EEPROM to SD");
      loggableMsg.storeToSd();
    }    
  }
  
  EepromMgr::getInstance()->resetPushIndices();
  
  // TODO: move msgs
}

LoggableParameters::LoggableParameters()
{
  blob_.data = NULL;
  blob_.size = 0;
  initialized_ = false;
}

LoggableParameters::~LoggableParameters() {}

uint8_t LoggableParameters::retrieveFromEeprom()
{
  Serial.println("In LoggableParameters::retrieveFromEeprom()");
  
  EepromMgr* eepromMgr = EepromMgr::getInstance();
    
  // Set up the blob with compressed data
  compress();

  eepromMgr->pullParameters(&blob_);
  
  printParameters(&parameters_);
}

uint8_t LoggableParameters::storeToEeprom()
{
  Serial.println("In LoggableParameters::storeToEeprom()");
  if (!initialized_)
  {
    retrieveFromEeprom();
    initialized_ = true;
  }
  
  printParameters(&parameters_);
  
  EepromMgr* eepromMgr = EepromMgr::getInstance();
    
  // Set up the blob with compressed data
  compress();

  eepromMgr->pushParameters(&blob_);
}

uint8_t LoggableParameters::compress()
{
  if (blob_.data == NULL)
  {
    blob_.size = sizeof(persistentParameters_t);
    blob_.data = (byte*)(&parameters_);
  }
}

uint8_t LoggableParameters::checkStationName()
{
  
}

uint8_t LoggableParameters::setErrorFlag(const bool flag)
{
  Serial.println("In LoggableParameters::setErrorFlag()");
  
  if (!initialized_)
  {
    retrieveFromEeprom();
    initialized_ = true;
  }
  
  Serial.print("Stored error flag: ");
  Serial.println((int)(parameters_.errorFlag));
  
  Serial.print("Passed error flag: ");
  Serial.println((int)flag);
  
  if (flag != parameters_.errorFlag)
  {
    Serial.println("Passed error flag differed from stored flag");
    parameters_.errorFlag = flag;
    storeToEeprom();
  }
}

bool LoggableParameters::getErrorFlag()
{
  if (!initialized_)
  {
    retrieveFromEeprom();
    initialized_ = true;
  }
  
  return parameters_.errorFlag;
}

uint8_t LoggableParameters::setSdConnected(const bool sdConnected)
{
  Serial.println("In LoggableParameters::setSdConnected()");
  
  if (!initialized_)
  {
    retrieveFromEeprom();
    initialized_ = true;
  }
  
  Serial.print("Stored flag: ");
  Serial.println((int)(parameters_.sdConnected));
  
  Serial.print("Passed flag: ");
  Serial.println((int)sdConnected);
  
  if (sdConnected != parameters_.sdConnected)
  {
    Serial.println("Passed flag differed from stored flag");
    parameters_.sdConnected = sdConnected;
    storeToEeprom();
  }
  
}

bool LoggableParameters::getSdConnected()
{
  if (!initialized_)
  {
    retrieveFromEeprom();
    initialized_ = true;
  }
  
  return parameters_.sdConnected;
}

uint8_t LoggableParameters::setStationName(const char* name)
{
  if (!initialized_)
  {
    retrieveFromEeprom();
    initialized_ = true;
  }
  
  if (strcmp(name, parameters_.stationName) != 0)
  {
    strncpy(parameters_.stationName, name, MAX_STATION_NAME_LEN);
    storeToEeprom();
  }
}

const char* LoggableParameters::getStationName()
{
  return(parameters_.stationName);
}


LoggableMdr::LoggableMdr(const mdr_t* mdrPtr, const LogTimestamp* timestampPtr) : stampedRecord_(NULL)
{
  if (mdrPtr == NULL)
  {
    // By default, use a pointer to the global mdr (avoid allocating RAM)
    mdr_ = &mdr;
  }
  else
  {
    mdr_ = mdrPtr;
  }
  
  if (timestampPtr == NULL)
  {
    // By default, use a pointer to the global logTimestamp (avoid allocating RAM)
    timestamp_ = &logTimestamp;
  }
  else
  {
    timestamp_ = timestampPtr;
  }
}

LoggableMdr::~LoggableMdr()
{
  if (stampedRecord_) free(stampedRecord_);
}

uint8_t LoggableMdr::storeToSd()
{
  SdMgr* mgr = SdMgr::getInstance();
  
  // TODO: call expand() directly, and use stampedRecord_
  char* record = getExpandedRecord();
  
  mgr->pushMdr(record);
}

uint8_t LoggableMdr::store()
{
  // Serial.println("In LoggableMdr::store()");
  // Serial.print("mdr.temp: ");
  // Serial.println(mdr_->temp);
  // Serial.print("mdr.hum ");
  // Serial.println(mdr_->hum);
  // Serial.print("mdr.press ");
  // Serial.println(mdr_->press);
  // Serial.flush();

  timestamp_->setNow();
  if (sdConnected)
  {
    storeToSd();
  }
  
  // sdConnected may have changed to false in the attempt to store above
  if (!sdConnected)
  {
    EepromMgr* mgr = EepromMgr::getInstance();
    
    // Set up the timestamp blob with compressed timestamp data
    logBlob_t* timestampBlob = timestamp_->getCompressed();

    // Set up the mdr blob with compressed mdr data
    compress();
    mgr->pushMdr(timestampBlob, &mdrBlob_);
  }
    
  // Serial.print("mdrBlob_.size: ");
  // Serial.println(mdrBlob_.size);
  // Serial.print("mdrBlob_.data: ");
  // for (int i = 0; i < mdrBlob_.size; i++)
  // {
  //   Serial.print((unsigned char)(mdrBlob_.data[i]));
  //   Serial.print(" ");
  // }
  // Serial.println();
}

uint8_t LoggableMdr::retrieveFromEeprom()
{
  uint8_t pullResult = 0;
    
  EepromMgr* eepromMgr = EepromMgr::getInstance();
  
  // Set up the timestamp blob with compressed timestamp data
  logBlob_t* timestampBlob = timestamp_->getCompressed();
  
  // Set up the mdr blob with compressed mdr data
  compress();
  
  pullResult = eepromMgr->pullMdr(timestampBlob, &mdrBlob_);
  // If there are no more mdrs to pull from EEPROM
  if (pullResult == 1)
  {
    return pullResult;
  }
  
  // Convert the compressed timestamp to native format
  timestamp_->uncompress();
  
  // Convert the compressed mdrBlob to native format
  uncompress();
  
  return pullResult;
}

// TODO: remove?
mdr_t* LoggableMdr::getMdr()
{
  return mdr_;
}

const char* LoggableMdr::getExpandedRecord()
{
  expand();
  return stampedRecord_;
}


// For now, "compress" the mdr data by pouring it into a blob
// TODO: set up the timestamp blob in this method (instead of in the caller)
// TODO: take advantage of loose precision requirements to compress more effectively
uint8_t LoggableMdr::compress()
{
  mdrBlob_.data = (byte*)mdr_;
  mdrBlob_.size = sizeof(mdr_t);
}

// For now, no action needed, because mdrBlob_ is not really compressed, and 
// mdrBlob_ already points to mdr_
// TODO: uncompress the timestamp in this method (instead of in the caller)
uint8_t LoggableMdr::uncompress()
{
}

// Expand native data into a timestamped record
uint8_t LoggableMdr::expand()
{
  Serial.println("In LoggableMdr::expand()");
  if (stampedRecord_ == NULL)
  {
    stampedRecord_ = malloc(expandedSize);
  }
  strncpy(stampedRecord_, loggableParameters.getStationName(), MAX_STATION_NAME_LEN);
  strcat(stampedRecord_, ",");
  strncat(stampedRecord_, timestamp_->getExpanded(), LogTimestamp::expandedSize);
  strcat(stampedRecord_, ",");
  ftoa(mdr_->temp, strtail(stampedRecord_));
  strcat(stampedRecord_, ",");
  ftoa(mdr_->hum, strtail(stampedRecord_));
  strcat(stampedRecord_, ",");
  ftoa(mdr_->press, strtail(stampedRecord_));
  
  return 0;
}


LoggableMsg::LoggableMsg(const logMessages::msgId_t msgId, const LogTimestamp* timestampPtr)
{
  code_ = msgId;
  expandedMsg_ = NULL;
  memcpy_P(&localMsg_, &logMessages::message_p[code_], sizeof(logMessages::msg_t));
  
  if (timestampPtr == NULL)
  {
    // By default, use a pointer to the global logTimestamp (avoid allocating RAM)
    timestamp_ = &logTimestamp;
  }
  else
  {
    timestamp_ = timestampPtr;
  }
}

LoggableMsg::~LoggableMsg()
{
  if (expandedMsg_)
  {
    free(expandedMsg_);
  }
}

static uint8_t LoggableMsg::log(const logMessages::msgId_t msgId)
{
  // Serial.println("In LoggableMsg::log()");
  // Serial.flush();
  // Serial.print("msgId = ");
  // Serial.println(msgId);
  // Serial.flush();
  LoggableMsg msg(msgId);
  msg.store();
}

uint8_t LoggableMsg::store()
{
#ifdef PRINT_LOG_MESSAGES_TO_SERIAL
  Serial.println((const __FlashStringHelper*)(localMsg_.text_p));
#endif

  timestamp_->setNow();
  if (sdConnected)
  {
    storeToSd();
  }
  
  // sdConnected may have changed to false in the attempt to store above
  if (!sdConnected)
  { 
    // Only store to EEPROM if the level is error
    if (localMsg_.level == logMessages::error)
    {
      logBlob_t* timestampBlob = timestamp_->getCompressed();

      EepromMgr* mgr = EepromMgr::getInstance();
      
      mgr->pushMsg(timestampBlob, code_);
    }
  }
}

uint8_t LoggableMsg::storeToSd()
{
  using namespace logMessages;
  
  SdMgr* mgr = SdMgr::getInstance();
  char codeString[4] = ""; // Enough characters for 3 digits + NULL terminating 
  
  const char localLevelName[LOG_MESSAGE_LEVEL_LEN];
  strncpy_P(localLevelName, (char*)pgm_read_word(&(levelName_p[localMsg_.level])), LOG_MESSAGE_LEVEL_LEN);
  const __FlashStringHelper* msgText = (const __FlashStringHelper*)(localMsg_.text_p);
  
/*
  Serial.print("In LoggableMsg::storeToSd(), code_: ");
  Serial.println(code_);
  Serial.print("(int)(levelName[localMsg_.level]): ");
  Serial.println((int)(levelName[localMsg_.level]));
  Serial.print("(int)(levelName[0]): ");
  Serial.println((int)(levelName[0]));
  Serial.print("(const __FlashStringHelper*)(levelName[0]): ");
  Serial.println((const __FlashStringHelper*)(levelName[0]));
  Serial.print("localLevelName: ");
  Serial.println(localLevelName);
  
  Serial.print("localMsg_.level: ");
  Serial.println(localMsg_.level);
  Serial.print("(int)(localMsg_.text): ");
  Serial.println((int)(localMsg_.text));
  Serial.print("(const __FlashStringHelper*)(localMsg_.text): ");
  Serial.println((const __FlashStringHelper*)(localMsg_.text));
  Serial.print("(int)(levelName[localMsg_.level]): ");
  Serial.println((int)(levelName[localMsg_.level]));
*/

  mgr->pushMsg("[");
  mgr->pushMsg(timestamp_->getExpanded());
  mgr->pushMsg("], ");
  mgr->pushMsg(localLevelName);
  mgr->pushMsg(": ");

  if (localMsg_.level == error)
  {
    mgr->pushMsg("(Code: ");
    itoa(code_, codeString, 10);
    mgr->pushMsg(codeString);
    mgr->pushMsg(") ");
  }
  
  mgr->pushMsg(msgText);
  mgr->pushMsg("\n");
}

uint8_t LoggableMsg::retrieveFromEeprom()
{
  uint8_t pullResult = 0;
    
  EepromMgr* eepromMgr = EepromMgr::getInstance();
  
  // Set up the timestamp blob with compressed timestamp data
  logBlob_t* timestampBlob = timestamp_->getCompressed();
  
  // Set up the mdr blob with compressed msg data
  // compress();
  
  pullResult = eepromMgr->pullMsg(timestampBlob, &code_);
  // If there are no more mdrs to pull from EEPROM
  if (pullResult == 1)
  {
    return pullResult;
  }
  
  // Convert the compressed timestamp to native format
  timestamp_->uncompress();
  
  // Convert the compressed msg to native format
  // uncompress();
  
  return pullResult;
}

