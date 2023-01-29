# EEPROM Usage

## 📃 Description

The EEPROM is a small data storage sector of the Arduino Nano Every (The board
intended to be used for this project) that will be used to hold data that
shouldn't be saved to the SD card at the time, and instead be saved to the
board itself. This table defines how that data should be saved and written.

## Usage Table

|Byte Position|Storage Description|
|-|-|
|0 to 24|System Name (Stored for convenience purposes and to ensure the SD card has the right name linked to the right account, which is more useful for multi-system setups)|
|25 to X|Other persistent parameters
|X+1 to 256|Various backup logs each stored in the [following backup log format](#❗-backup-log-format)|

### Backup log format

(Each log currently takes up **32 bytes**)

|Byte Size|Storage Description|
|-|-|
|20 Bytes|Date and time recorded|
|4 Bytes|Temperature (float)|
|4 Bytes|Humidity (float)|
|4 Bytes|Pressure (float)|
