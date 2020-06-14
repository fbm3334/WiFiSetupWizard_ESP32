# WiFiSetupWizard_ESP32

## Description

WiFiSetupWizard_ESP32 is designed to be a simple to use WiFi setup utility for the Espressif ESP32 using the arduino-esp32 libraries, therefore making it easy to integrate into Arduino/PlatformIO projects using the ESP32. It uses serial communication with the ESP32 (UART_0) to communicate externally, meaning that WiFi connections can be set up using terminal emulator software on a PC or other device.
## Features
 - Simple to use - a total of 6 lines of code are required in order to add the utility
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
![Display of Arduino library location](https://github.com/fbm3334/WiFiSetupWizard_ESP32/blob/master/img/ArduinoLib.png)

## Future additions
Some features that are missing and can be added in the future include:

 - [ ] WEP support for networks
 - [ ] 
## Licensing
This library is licensed under the MIT license. Please refer to the license for terms of use.
<!--stackedit_data:
eyJoaXN0b3J5IjpbMTY4NTYxOTg0NCwtMTQwMzE3NDY1OCwtMT
MzNzQ5NTQzMSwxNTU4NTAyODI1LDE1ODg3NDgwMzAsMjA0NTE2
NjI2MSwxOTY4NjQxMzQzLC03NzEzOTY4NjRdfQ==
-->