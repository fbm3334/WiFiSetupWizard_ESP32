This document explains how to use the WiFi Setup Wizard to set up WiFi connections. For examples of incorporating the wizard into your program, look in the examples folder.

# Terminal emulation
You will need to use a terminal emulation program in order to use the wizard. I use [CoolTerm](https://freeware.the-meiers.org), but other terminal emulation programs are available. In order to get the best experience, I recommend the following settings:

 - Baud rate - 115200 (this can be varied as long as it matches the setup() baud rate)
 - Data/parity/stop bits - 8-N-1
 - Enter key emulation - CR+LF
 - Form feed to clear screen (if possible in the terminal emulation program)
 
# Connection process
The wizard follows this order of connection:
1. Attempt to connect using stored settings
	Settings are stored on the non-volatile storage of the ESP32 (using the Preferences library)
2. Launch the wizard if this is not successful

## Using the wizard
### Connecting using stored settings
When using stored settings, connection is designed to not require a serial connection (i.e. the ESP32 will connect as soon as it receives power). Serial output is still produced to show the connection state.
![Connection using stored settings - CoolTerm output](https://github.com/fbm3334/WiFiSetupWizard_ESP32/blob/master/img/CoolTerm_NVS_conn.png)

*(The garbled SSID input is, I believe, due to the way iOS formats apostrophes as Unicode rather than using an ASCII apostrophe)*

If connection using stored settings is unsuccessful, then the main wizard will be launched.
### Connection wizard
The connection wizard can either be launched by pressing Space in the first 5 seconds after serial connection is established or if connection using stored settings is unsuccessful.

The main view of the connection wizard has four options, which are selected by pressing the appropriate key on the keyboard:

 - a - Advanced network view
	 - Displays a more advanced view of the networks, showing the following properties:
		 - SSID
		 - Signal strength in dBm
		 - Signal strength in bars
		 - MAC address of access point
		 - Encryption type
		 - 2.4GHz channel
	- Press Space to exit.
- d - Connect using DHCP
- s - Connect using static IP/custom DNS
- r - Rescan networks (restarts the wizard)

