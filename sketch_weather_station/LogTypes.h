#ifndef LOGTYPES_H
#define LOGTYPES_H

#include <Arduino.h>
#include "defs.h"


typedef struct
{
  unsigned char size;
  byte* data;
} logBlob_t;

typedef struct
{
  uint8_t mon;
  uint8_t day;
  uint16_t year;
  uint8_t hr;
  uint8_t min;
  uint8_t sec;
} logTime_t;

typedef struct 
{
  char stationName[MAX_STATION_NAME_LEN + 1];
  int ptcConst; // phototransistor calibration constant
  bool errorFlag;
  bool sdConnected;
} persistentParameters_t;

const uint8_t compressedParamsSize = sizeof(persistentParameters_t);

typedef struct
{
  float temp;
  float hum;
  float press;
} mdr_t;

char* strtail(const char* src);
void ftoa(float f, char *str);

class LogTimestamp
{
  public:
  LogTimestamp();
  LogTimestamp(const logBlob_t* blob);
  LogTimestamp(const logTime_t* time);
  ~LogTimestamp();
  
  const static uint8_t compressedSize = 7; // size in bytes of the blob returned by getCompressed()
  const static uint8_t expandedSize = 20;
  
  void setNow();
  const logBlob_t* getCompressed();
  uint8_t uncompress();
  const logTime_t* getNative();
  const char* getExpanded();
  
  private:
  
  logTime_t time_;
  
  logBlob_t blob_;
  char* expanded_;
};

extern LogTimestamp logTimestamp;

#endif
