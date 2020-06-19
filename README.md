# WiFiSetupWizard_ESP32

## Description

WiFiSetupWizard_ESP32 is designed to be a simple to use WiFi setup utility for the Espressif ESP32 using the arduino-esp32 libraries, therefore making it easy to integrate into Arduino/PlatformIO projects using the ESP32. It uses serial communication with the ESP32 (UART_0) to communicate externally, meaning that WiFi connections can be set up using terminal emulator software on a PC or other device.
## Features
 - Simple to use - a total of 6 lines of code are required in order to add the utility, and the utility runs entirely within the setup() portion of the code, meaning that the loop() portion of the code is free
 - Lightweight - does not use much more RAM or program storage space on top of the resources required to use WiFi on the ESP32
 - WiFi credentials storage using the NVS (non-volatile storage) on the ESP32

## Using the library
**PlatformIO**  
If you are using PlatformIO, place the /lib/WiFiSetup folder from this repository into the /lib folder of your project. Then, follow the example in /src/main.cpp to incorporate the wizard into your project.
**Arduino**
To use the library, copy the /lib/WiFiSetup folder from the repository and paste it into your Arduino libraries folder:
*Typical locations:*
- Windows: C:\Users\your_user\My Documents\Arduino\libraries
- macOS: /Users/your_user/Documents/Arduino/libraries
- Linux: /home/your_user/Arduino/libraries
Then, restart your Arduino IDE and the library should appear in the Sketch/Include Library menu as WiFiSetup, as shown:

![WiFiSetup library location in Sketch menu in Arduino IDE](https://github.com/fbm3334/WiFiSetupWizard_ESP32/blob/master/img/ArduinoLib_nonretina.png)

### Using the wizard
Please refer to [Usage.md](https://github.com/fbm3334/WiFiSetupWizard_ESP32/blob/master/Usage.md) for instructions on using the wizard.

## Future additions
Some features that are missing and can be added in the future include:
 - [ ] ESP8266 support
 - [ ] Status LED support (e.g. using an RGB LED to indicate connection status)
 - [ ] WEP encryption support - I have decided not to add it as WEP has been deprecated since 2004 and is extremely insecure (see [this article](http://www.isaac.cs.berkeley.edu/isaac/wep-faq.html) from researchers from the University of California, Berkeley for details).
## Licensing
This library is licensed under the MIT license. Please refer to the license for terms of use.
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTI5MzE0MjQzNywtNTY2OTk0MTU3LDY4OD
U5ODg2NCwtMTA2ODgxMDMyMywtODAyOTk2MDM3LDg3NjE1MjUz
OCwtMTQwMzE3NDY1OCwtMTMzNzQ5NTQzMSwxNTU4NTAyODI1LD
E1ODg3NDgwMzAsMjA0NTE2NjI2MSwxOTY4NjQxMzQzLC03NzEz
OTY4NjRdfQ==
-->
