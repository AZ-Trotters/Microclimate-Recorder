#ifndef LOG_H
#define LOG_H

#include <SD.h>

// Debug Setup

/*
LOG LEVELS:
0 - Silent (nothing)
1 - Error (errors only)
2 - Warning (errors and warnings)
3 - Notice (errors, warnings, and notices)
4 - Verbose (everything)
WHEN LOGGING:
1 - Error (this is an error)
2 - Warning (this is a warning)
3 - Notice (this is helpful info)
4 - Debug (used for troubleshooting)
*/

#define LOG_LEVEL 4
#define PRINT_LOG_MESSAGES_TO_SERIAL
#define ERROR_LOG_FILENAME F("statInfo/errorlog.txt")

#define LOG_ERROR(x)
#define LOG_ERROR(x) logToSD(1, (x))

#define LOG_WARNING(x)
#define LOG_WARNING(x) logToSD(2, (x))

#define LOG_NOTICE(x)
#define LOG_NOTICE(x) logToSD(3, (x))

#define LOG_DEBUG(x)
#define LOG_DEBUG(x) logToSD(4, (x))

#define FLASH_STRING_HELPER_LEN 80

void createErrorLogEntry(int logTypeId, const char *logMessage, File logFile);

void logToSD(int logTypeId, const __FlashStringHelper *logMessage);

void logToSD(int logTypeId, const char *logMessage);


#endif