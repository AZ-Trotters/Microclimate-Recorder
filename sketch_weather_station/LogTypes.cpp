/******************************************************************************
This module contains common utility classes used by other classes (e.g. 
Loggables and LogStorageMgrs) in the process of storing and retrieving logged 
records

Dependencies:
- TimeLib library
******************************************************************************/
#include "LogTypes.h"
#include <TimeLib.h>

LogTimestamp logTimestamp;

char* strtail(const char* src)
{
  return (char*)(src + strlen(src));
}

void ftoa(float f, char *str)
{
  int intPart = (int)f;
  int decPart = (int)(f * 100) % 100;
  
  itoa(intPart, str, 10);
  strcat(str, ".");
  itoa(decPart, strtail(str), 10);
}

LogTimestamp::LogTimestamp() : expanded_(NULL)
{}

LogTimestamp::LogTimestamp(const logBlob_t* blob) : expanded_(NULL)
{
  memcpy(&time_, blob->data, sizeof(time_));
}

LogTimestamp::LogTimestamp(const logTime_t* time) : expanded_(NULL)
{
  memcpy(&time_, time, sizeof(time_));
}

LogTimestamp::~LogTimestamp()
{
  if (expanded_) free(expanded_);
}

void LogTimestamp::setNow()
{
  time_.mon = month();
  time_.day = day();
  time_.year = year();
  time_.hr = hour();
  time_.min = minute();
  time_.sec = second();
}

// For now, "compress" the time data by putting it in a single struct
// TODO: take advantage of the constraints of time data elements to compress more effectively
const logBlob_t* LogTimestamp::getCompressed()
{
  setNow();
  blob_.size = sizeof(time_);
  blob_.data = (void*)(&time_);
  return &blob_;
}

// For now, no action needed, because blob_ is not really compressed, and 
// blob_ already points to time_
uint8_t LogTimestamp::uncompress()
{
}

const logTime_t* LogTimestamp::getNative()
{
  return &time_;
}

const char* LogTimestamp::getExpanded()
{
  if (expanded_ == NULL)
  {
    expanded_ = malloc(expandedSize);
  }
  // Serial.print("time_.mon: ");
  // Serial.println(time_.mon);
  // Serial.print("time_.day: ");
  // Serial.println(time_.day);
  // Serial.print("time_.year: ");
  // Serial.println(time_.year);

  itoa(time_.mon, expanded_, 10);
  strcat(expanded_, "/");
  itoa(time_.day, strtail(expanded_), 10);
  strcat(expanded_, "/");
  itoa(time_.year, strtail(expanded_), 10);
  strcat(expanded_, " ");
  itoa(time_.hr, strtail(expanded_), 10);
  strcat(expanded_, ":");
  itoa(time_.min, strtail(expanded_), 10);
  strcat(expanded_, ":");
  itoa(time_.sec, strtail(expanded_), 10);
  
  // Serial.print("complete expanded_: ");
  // Serial.println(expanded_);
    
  return expanded_;
}
