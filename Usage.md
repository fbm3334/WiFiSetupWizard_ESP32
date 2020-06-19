This document explains how to use the WiFi Setup Wizard to set up WiFi connections. For examples of incorporating the wizard into your program, look in the examples folder.

The wizard supports open and WPA/WPA2 encrypted networks - WPA Enterprise and WEP are not supported (the former due to a lack of support within the ESP32 libraries and the latter due to security issues and lack of use in 2020).

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

#### Using DHCP
1. Press 'd' on the keyboard to enter DHCP connection mode. 
2. Then, select the network you wish to connect to from the list by typing its number and pressing Enter.
3. If WPA encryption is being used, you will need to enter the passphrase by typing it in and pressing Enter.
4. Conection will be attempted - if the connection is successful, the SSID and password will be saved into non-volatile storage. Otherwise, the wizard will restart.

#### Using static IP/custom DNS
1. Press 's' on the keyboard to enter static IP/custom DNS connection mode. 
2. The following IP addresses need to be entered in this order when prompted:
    - Static IP
    - Gateway IP (router IP)
    - Subnet mask
   
To enter these, type in the IP address in the usual format (e.g. to enter 255.255.255.0, simply type in 255.255.255.0) and press Enter.
3. You will be prompted to set up a custom DNS - press 'd' to use a custom DNS or 'n' to use the gateway/router DNS. DNS IP addresses are entered in the same way as for the static IP etc.
4. Then, select the network you wish to connect to from the list by typing its number and pressing Enter.
5. If WPA encryption is being used, you will need to enter the passphrase by typing it in and pressing Enter.
6. Conection will be attempted - if the connection is successful, the SSID and password will be saved into non-volatile storage. Otherwise, the wizard will restart.

