# WiFiSetupWizard_ESP32

## Description

ESP32_WiFiSetup is designed to be a simple to use WiFi setup utility for the Espressif ESP32. It uses the ESP32's USB serial functionality to communicate externally, meaning that WiFi connections can be set up using terminal emulator software on a PC or other device.
## Features

 - Simple to use - a total of 6 lines of code are required in order to add the utility
 - Lightweight - does not use much more RAM or program storage space on top of the resources required to use WiFi on the ESP32
 - WiFi credentials storage using the NVS (non-volatile storage) on the ESP32

## Using the library
**PlatformIO**  
If you are using PlatformIO, place the /lib/WiFiSetup folder from this repository into the /lib folder of your project. Then, follow the example

## Future additions
Some features that are missing and can be added in the future include:

 - [ ] WEP support for networks
 - [ ] 

<!--stackedit_data:
eyJoaXN0b3J5IjpbLTE1ODk4ODkwMTUsLTc3MTM5Njg2NF19
-->