# statName.txt

## 📝 Written by: Computer/Application

## 📕 Read by: Weather Station/Computer/Application

* StatName.txt houses a new name for the Arduino weather station to identify
itself as.
* This value is saved to the first 25 bytes of EEPROM.

## ⚠ Limitations

* This value must be 24 bytes (roughly 24 chars) or less to avoid EEPROM corruption.
* This value should not include any whitespace characters.
