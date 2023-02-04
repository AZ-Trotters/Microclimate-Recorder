# Error Codes

While you're using your Microclimate Recorder, you may see a red light after pressing the SD removal button. This means you should check the SD file "statInfo/errorlog.txt" for any error codes. Here's what they mean in detail:

|Error Code|Error Message|
|-|-|
|0|A Realtime Clock was not found. System has halted, and must be rebooted. The clock module of your system is not securely connected to the main microcontroller.|
|1|Realtime Clock ran out of battery power. Replace the battery on the clock module to ensure it can keep its charge.|
