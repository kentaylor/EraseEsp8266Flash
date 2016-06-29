# Erase Flash
It is possible to write data into flash that will cause an ESP8266 to fail to connect to WiFi even after new code is uploaded using the Arduino SDK, LUA or over the air programming which could be considered as bricking the device. This simple sketch is for recovering the bricked ESP8266 device by erasing all of the flash memory and thus removing the corrupted data. 

Subsequent program uploads will then work fine using the Arduino IDE and over the air programming after the first Arduino upload.

## How To Use This Sketch

This sketch is unusual in that after it runs once the ESP8266 will do nothing until it has been flashed again with another sketch. This is because this sketch completely erases the flash, including erasing itself. It runs from RAM so is able to continue after being erased until it completes. It is best run with the Arduino serial monitor open to observe the progress of the erasure including any failed erasure, which may occur with damaged flash. It is possible to wear out flash if it has been written too many times. Usually this occurs when flash writes are repeated in a tight program loop.

The sketch will run immediately after upload, completely erase the flash then crash, leaving the device unbootable. When the Arduino IDE uploads a new sketch it will also upload all of the necesary supporting firmware for the ESP8366 to function normally.

## Why Is This Sketch Useful?

There are some parts of flash where data resides that is preserved when a new program is uploaded. In particular WiFi configuration data is retained. If this data becomes corrupted it will not be overwritten and remain faulty.

## What Causes Flash Corruption?

You can write anywhere you wish into flash so any user program could potentially corrupt the flash but it is unlikely. A [ bug in the ESP core library ] (https://github.com/esp8266/Arduino/issues/1997) has been the sole cause for me.

While I've had frequent flash corruptions the effects are random. Calling WiFi.begin(SSID, Password) with a different SSID or password to those already in non volatile memory or calling WiFi.begin() should not be done while it is trying to connect to a network and calling at other times may cause corruption also. It will usually be OK but sometimes will corrupt memory, depending, I suspect, on what stage it is up to in the connection process. Once it has failed, rebooting will usually be enough to connect again to WiFi. Rewriting the WiFi credentials can usually stop problems with future WiFi connections. 

## Will My ESP8266 Device Suffer Bricking?

Probably not, as the [bug causing the problem ] (https://github.com/esp8266/Arduino/issues/1997)has been fixed. 

As well this bug only occasionally caused WiFi connectivity to permanently fail which probably explains why it existed so long before it was correctly identified. Once identified it was quickly fixed. Some of us have found this bug extremely frustrating due to the difficulty in trying to deal with failure modes that were not repeatable. 

## Some Of The Frustration

Looking through the issues reported and code revisions in WiFi manager I can see discussion of the same problems I was having and efforts to fix them. Specifically:-
- There has been an attempt to fix a problem identified as an ["auto connect racing issue"] ( https://github.com/tzapu/WiFiManager/commit/b99487785d2c8319df1223b204e1bba2b321f3f3) by not calling WiFi.begin under some circumstances. This fix has a side effect identified in [issue 141](https://github.com/tzapu/WiFiManager/issues/141) that "WiFiManager will not connect to a newly selected access point if a connection to another access point already exists."
- Issue [149] (https://github.com/tzapu/WiFiManager/issues/149) Problem is a side effect of trying to manage WiFi connectivity in code.
- Issue [147](https://github.com/tzapu/WiFiManager/issues/147) I think this issue is occuring because WiFi.begin was called when it wasn't required. There is a probability it will fail every time it is called but when deep sleep is used with frequent wakeups the cumulative probability of failure becomes high. Tzapu said he had seen the same problem once.
- Issue [143](https://github.com/tzapu/WiFiManager/issues/143) Looks like it may be same issue as issue 149 but its not clear from the information provided.
- Issue [102](https://github.com/tzapu/WiFiManager/issues/102) Arises when WiFi.begin called when already connected.
- Issue[71](https://github.com/tzapu/WiFiManager/issues/71) Assumes that WiFi.begin is required when it isn't.
