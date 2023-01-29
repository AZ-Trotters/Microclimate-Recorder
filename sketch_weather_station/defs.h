#ifndef DEFS_H
#define DEFS_H

#ifdef __AVR_ATmega4809__
  #define NANO_EVERY
  #define ENV_SENSOR_PRESENT
  #undef LOW_POWER_LIBRARY
  #undef LOW_POWER_SLEEP
#else
  #undef NANO_EVERY
  #define ENV_SENSOR_PRESENT
  #define LOW_POWER_LIBRARY
  #define LOW_POWER_SLEEP
#endif

#define MAX_STATION_NAME_LEN 24 // MAX_STATION_NAME_LEN must be less than 256

#define SIMULATED_POWER_OFF

#endif