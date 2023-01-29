# weather-station-project

Arduino project and related info files for use in outdoor weather station
project

* System comes on every 2 hours
* System records weather values from weather sensor to inserted SD Card
* Button press of sensor prompts data finalization for SD removal
* Data can be read on a computer or with simple application (not developed
yet) via files saved from Arduino

## 📜 Task List (Priorities 1 and 2 are needed for first prototype)

* [x] Realtime Clock Functionality
* [x] SD Card Read/Write
* [x] Turn on red light when saving data to SD Card
* [x] Save stationName.txt to EEPROM if it is different from currently-saved
data
* [x] Save csv data to SD card when turned on
* [x] Get "statOpts/time.txt" from SD card on wake to adjust the RTC's current
time
* [x] Error logging (in statInfo/errorlog.txt)
* [X] Pause/Finish writing to SD Card when button is pressed
  * [X] :one: All data and error logs should finish if Arduino was running
  * [X] :two: Record the current time on the SD card
  * [X] :three: Button should somehow wakeup Arduino?
* [X] :one: Save weather data to EEPROM if SD card not present
* [X] :two: Move weather data from EEPROM to SD card when SD card is replaced
* [X] :two: Save error logs to EEPROM if SD card not present
* [X] :two: Move error logs from EEPROM to SD card when SD card is replaced
* [X] :two: Include station identifier in weather data records on SD card
* [ ] :three: Monitor and provide battery voltage (save to SD card on wake)
* [ ] :three: Add dependency list here including library names and
versions used for Arduino upload
* [ ] :three: Alphabetize all variable and function declarations
* [ ] :three: Error indicator LED
* [ ] :three: OK to remove SD card LED
* [ ] :three: Red light should indicate (multiple blinks?) that stationName on
SD (statInfo) is not the same as station name (User put wrong SD in wrong system
in multi-system setup)

## 🛠 Build Dependencies

### 📚 Third-Party Libraries

<!-- [SD@1.2.4](https://www.arduino.cc/reference/en/libraries/sd/) -->
* [Adafruit BusIO@1.14.1](https://github.com/adafruit/Adafruit_BusIO)
* [RTClib@2.1.1](https://github.com/adafruit/RTClib)
* [LowPower_LowPowerLab@2.2.0](https://github.com/LowPowerLab/LowPower)
* [M5Unit-ENV@0.0.6 (Included in sketch_weather_station folder)](https://github.com/m5stack/M5Unit-ENV/releases/tag/0.0.6)

### 💻 Arduino IDE (Uploader)

Version 2.0.3
