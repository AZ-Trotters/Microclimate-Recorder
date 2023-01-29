/******************************************************************************
This module contains classes to manage data storage devices (e.g. SD card,
EEPROM) on which loggable data is stored and retrieved.
These classes are responsible for:
- managing sessions to storage devices
- keeping track of which addresses are used and which are available

Dependencies:
- LogTypes
- EEPROM library
- SD library
******************************************************************************/
#include "LogStorageMgrs.h"
#include "LogTypes.h"
#include <EEPROM.h>

#define EEPROM_STORAGE_OFFSET 0
#define EEPROM_SIZE 256
#define EEPROM_MDR_INDEX_ADDR 255
#define EEPROM_MSG_INDEX_ADDR EEPROM_STORAGE_OFFSET + compressedParamsSize
#define SD_DIRECTORY_COUNT 2

extern bool sdConnected;
extern const uint8_t compressedParamsSize;

const char sdDirectories[SD_DIRECTORY_COUNT][10]
{
  "/statInfo",
  "/statOpts"
};

// Initialize the pointer to the single instances to NULL
EepromMgr* EepromMgr::instance_ = NULL;
SdMgr* SdMgr::instance_ = NULL;

void EepromPutBlob(uint8_t index, const logBlob_t* blob)
{
  // Serial.println("In EepromPutBlob()");
  for (uint8_t i = 0; i < blob->size; i++)
  {
    // Serial.print(index+i);
    // Serial.print(":");
    // Serial.print(blob->data[i]);
    // Serial.print(" ");
    EEPROM.write(index + i, blob->data[i]);
  }
  // Serial.println();
}

void EepromGetBlob(uint8_t index, logBlob_t* blob)
{
  for (uint8_t i = 0; i < blob->size; i++)
  {
    blob->data[i] = EEPROM.read(index + i);
  }
}

uint8_t EepromMgr::pullParameters(logBlob_t* blob)
{
  persistentParameters_t* parameters;
  parameters = (persistentParameters_t*)(blob->data);
  EEPROM.get(EEPROM_STORAGE_OFFSET, *parameters);
}

uint8_t EepromMgr::pushParameters(logBlob_t* blob)
{
  persistentParameters_t* parameters;
  parameters = (persistentParameters_t*)(blob->data);
  EEPROM.put(EEPROM_STORAGE_OFFSET, *parameters);
}

EepromMgr::EepromMgr(): mdrCnt_(0), msgCnt_(0)
{
  // start the msgIndex right after the persistent parameters, going forward
  // msgPushIndex_ = msgIndexAddress + 1; // Backup
  // EEPROM.write(msgIndexAddress, msgIndexAddress + 1); // initialize
  // Serial.print("Initialized msgpushIndex at ");
  // Serial.print(msgIndexAddress);
  // Serial.print(" to ");
  // Serial.println(msgIndexAddress + 1);
  msgPushIndex_ = EEPROM.read(EEPROM_MSG_INDEX_ADDR);
  msgPullIndex_ = EEPROM_MSG_INDEX_ADDR + 1;
  
  // start the mdrIndex at the highest address, going backward
  // mdrPushIndex_ = EEPROM_MDR_INDEX_ADDR; // If this is used as a backup, note that it needs to fit in mdrPushIndex_ data type
  // EEPROM.write(EEPROM_MDR_INDEX_ADDR, EEPROM_MDR_INDEX_ADDR); // initialize
  mdrPushIndex_ = EEPROM.read(EEPROM_MDR_INDEX_ADDR);
  // Serial.print("mdrPushIndex_: ");
  // Serial.println(mdrPushIndex_);
  mdrPullIndex_ = EEPROM_MDR_INDEX_ADDR;
}

EepromMgr * EepromMgr::getInstance()
{
  if (instance_ == NULL) instance_ = new EepromMgr();
  
  return instance_;
}

uint8_t EepromMgr::pushMdr(const logBlob_t* timestampBlob, const logBlob_t* mdrBlob)
{
  uint8_t address;
  if (mdrBlob->size != sizeof(mdr_t))
  {
    Serial.println("In Eeprom::pushMdr() - mdrBlob is the wrong size!");
    return -1;
  }
  // If this blob would overwrite messages
  if (mdrPushIndex_ - timestampBlob->size - mdrBlob->size < msgPushIndex_)
  {
    Serial.println("In Eeprom::pushMdr() - out of room");
    return -1;
  }
  
  // push the timestamp
  address = mdrPushIndex_ - LogTimestamp::compressedSize;
  // Serial.print("Putting timestamp to address: ");
  // Serial.println(address);
  EepromPutBlob(address, timestampBlob);
  
  // push the mdr
  address -= mdrBlob->size;
  // Serial.print("Putting mdr to address: ");
  // Serial.println(address);
  EepromPutBlob(address, mdrBlob);

  mdrCnt_++;
  mdrPushIndex_ = address;
  // Serial.print("Writing new mdrPushIndex_ to EEPROM: ");
  // Serial.println(mdrPushIndex_);
  EEPROM.write(EEPROM_MDR_INDEX_ADDR, mdrPushIndex_);
}

uint8_t EepromMgr::pullMdr(logBlob_t* timestampBlob, logBlob_t* mdrBlob)
{
  // if all mdr records on EEPROM have already been pulled
  if (mdrPullIndex_ <= mdrPushIndex_)
    return 1;

  uint8_t address = mdrPullIndex_;
  address -= timestampBlob->size;
  // Serial.print("Pulling timestamp from address: ");
  // Serial.println(address);
  EepromGetBlob(address, timestampBlob);
  
  address -= mdrBlob->size;
  // Serial.print("Pulling mdr from address: ");
  // Serial.println(address);
  EepromGetBlob(address, mdrBlob);
  
  mdrPullIndex_ = address;
  
  return 0;
}

uint8_t EepromMgr::pushMsg(logBlob_t *timestampBlob, compressedLogCode code)
{
  uint8_t address;
  // If this blob would overwrite messages
  if (msgPushIndex_ + timestampBlob->size + sizeof(compressedLogCode) > mdrPushIndex_)
  {
    Serial.println("In Eeprom::pushMsg() - out of room");
    Serial.println(msgPushIndex_);
    Serial.println(mdrPushIndex_);
    return 1;
  }
  
  // push the timestamp
  // Serial.print("Putting timestamp to address: ");
  // Serial.println(address);
  EepromPutBlob(msgPushIndex_, timestampBlob);
  address = msgPushIndex_ + LogTimestamp::compressedSize;
  
  // push the msg
  // Serial.print("Putting msg to address: ");
  // Serial.println(address);
  EEPROM.put(address, code);
  address += sizeof(compressedLogCode);

  msgCnt_++;
  msgPushIndex_ = address;
  // Serial.print("Writing new mdrPushIndex_ to EEPROM: ");
  // Serial.println(mdrPushIndex_);
  EEPROM.write(EEPROM_MSG_INDEX_ADDR, msgPushIndex_);
}

uint8_t EepromMgr::pullMsg(logBlob_t *timestampBlob, compressedLogCode* code)
{
  // if all mdr records on EEPROM have already been pulled
  if (msgPullIndex_ >= msgPushIndex_)
    return 1;

  uint8_t address = msgPullIndex_;
  // Serial.print("Pulling timestamp from address: ");
  // Serial.println(address);
  EepromGetBlob(address, timestampBlob);
  address += timestampBlob->size;
  
  // Serial.print("Pulling mdr from address: ");
  // Serial.println(address);
  EEPROM.get(address, *code);
  address += sizeof(compressedLogCode);
  
  msgPullIndex_ = address;
  
  return 0;
}

uint8_t EepromMgr::resetPushIndices()
{
  // Serial.println("Resetting EEPROM push indices");
  // Serial.flush();
  mdrPushIndex_ = EEPROM_MDR_INDEX_ADDR;
  EEPROM.write(EEPROM_MDR_INDEX_ADDR, mdrPushIndex_);
  msgPushIndex_ = EEPROM_MSG_INDEX_ADDR + 1;
  EEPROM.write(EEPROM_MSG_INDEX_ADDR, msgPushIndex_);
  // 
}

SdMgr::SdMgr()
{
}

static SdMgr * SdMgr::getInstance()
{
  if (instance_ == NULL) instance_ = new SdMgr();
  
  return instance_;
}

uint8_t SdMgr::pushMdr(const char* record)
{
  size_t printed = 0;
  
  // Serial.print("In SdMgr::pushMdr() with record: ");
  // Serial.println(record);
  openFile(WEATHER_DATA_FILENAME, mdrFile_);
  if (mdrFile_.size() == 0)
  {
    Serial.println(F("Size of weather values is 0"));
    createWeatherValueDefaultHeaders();
  }

  printed = mdrFile_.print(record);
  // Serial.print("Bytes printed to ");
  // Serial.print(WEATHER_DATA_FILENAME);
  // Serial.print(": ");
  // Serial.println(printed);
  
  // if 0 bytes are written
  if (mdrFile_.print("\n") == 0) sdConnected = false;
  mdrFile_.close();
  //   LOG_NOTICE("Writing to local memory because SD card wasn't connected");
}

uint8_t SdMgr::pushTimeNow()
{
  File file;
  LogTimestamp timestamp;
  timestamp.setNow();
  SD.remove(TIMESTAMP_FILENAME);
  openFile(TIMESTAMP_FILENAME, file);
  // file = SD.open(TIMESTAMP_FILENAME, FILE_WRITE);
  file.print(timestamp.getExpanded());
  file.close();
}

uint8_t SdMgr::pushMsg(const char* content)
{
  openFile(ERROR_LOG_FILENAME, msgFile_);
  if (msgFile_.print(content) == 0) sdConnected = false;
  msgFile_.close();
}

uint8_t SdMgr::pushMsg(const __FlashStringHelper* content) 
{
  openFile(ERROR_LOG_FILENAME, msgFile_);
  // Serial.print("In SdMgr::pushMsg() for flash string, content:");
  // Serial.println(content);
  if (msgFile_.print(content) == 0) sdConnected = false;
  msgFile_.close();
}

int8_t SdMgr::openFile(__FlashStringHelper* fileName, File& file)
{
  // If the file has not been opened yet
  if (!file)
  {
    createNeededSdDirectories();
    file = SD.open(fileName, FILE_WRITE);
    if (!file)
    {
      Serial.print("Failed to open file: ");
      Serial.println(fileName);
      return -1;
    }    
    // Serial.print("In SdMgr::getFile. Just opened file with name ");
    // Serial.println(fileName);
    // Serial.print("File size: ");
    // Serial.println(file.size());
  }
}

uint8_t SdMgr::createNeededSdDirectories()
{
  for (int i = 0; i < SD_DIRECTORY_COUNT; i++)
  {
    if (!SD.exists(sdDirectories[i]))
    {
      SD.mkdir(sdDirectories[i]);
    }
  }
}

uint8_t SdMgr::createWeatherValueDefaultHeaders()
{
  mdrFile_.print(F("\"Station Name\","));
  mdrFile_.print(F("\"Date/Time\","));
  mdrFile_.print(F("\"Temperature\","));
  mdrFile_.print(F("\"Humidity\","));
  mdrFile_.println(F("\"Pressure\""));
  // LOG_NOTICE(F("Created headers for weather values csv file"));
}