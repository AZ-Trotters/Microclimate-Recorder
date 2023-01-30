# errorlog.txt

Houses all errors that the Arduino accumulates over runtime. Creates a new line
for each new error, and includes:

* Date and Time of occurrence
* Log level (error, warning, notice, debug)
* Error code if applicable that may lead to more info on the issue
* Simple message describing what happened

## 💡 Example

```text
[246 msec since startup], Notice: Initialized system wakeup button
[01/21/2022 15:00:00], ERROR: (Code: 1003) Realtime Clock ran out of battery power. Replace the clock battery
```
