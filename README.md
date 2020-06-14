# WiFiSetupWizard_ESP32

## Description

ESP32_WiFiSetup is designed to be a simple to use WiFi setup utility for the Espressif ESP32 using the arduino-esp32 libraries. It uses the ESP32's USB serial functionality to communicate externally, meaning that WiFi connections can be set up using terminal emulator software on a PC or other device.
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


## Future additions
Some features that are missing and can be added in the future include:

 - [ ] WEP support for networks
 - [ ] 

<!--stackedit_data:
eyJoaXN0b3J5IjpbMTU4ODc0ODAzMCwyMDQ1MTY2MjYxLDE5Nj
g2NDEzNDMsLTc3MTM5Njg2NF19
-->