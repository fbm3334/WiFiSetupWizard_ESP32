#ifndef WIFISETUP_H
#define WIFISETUP_H

#include <Arduino.h>
#include <WiFi.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include <Preferences.h>

#define LENGTH_IP_CHAR 16

// Enum for holding WiFi signal strength (verbose)
enum VerboseSigStrength {Excellent, Good, Fair, Weak};

// Enum for holding connection type as integer
enum ConnectionType : uint8_t {
    UNKNOWN,
    OPEN_DHCP,
    OPEN_STATIC,
    OPEN_STATIC_DNS,
    WPA_DHCP,
    WPA_STATIC,
    WPA_STATIC_DNS
};

/** Struct to hold network data */
struct NetworkData {
    String network_ssid; /**< Network SSID */
    long network_signal_strength; /**< Network signal strength in dBm */
    VerboseSigStrength signal_verbose; /**< Verbose signal strength (Excellent, Good, Fair, Weak) */
    String network_mac; /**< Network MAC address, stored as string */
    wifi_auth_mode_t network_enc_type; /**< Network encryption type */
    int32_t network_chan; /**< Network channel */
};

/** \class WiFiSetup
 * \brief Sets up WiFi connections on the ESP32
 * \author Finn Beckitt-Marshall (fbm3334)
 * \date June 2020
 */

class WiFiSetup {

    Preferences prefs;

    public:
        /** Timeout flag */
        static bool connect_timeout;

        /** Hardware timer - used for connection timeout */
        static hw_timer_t * timer;

        /** Constructor */
        WiFiSetup();

        /** Destructor */
        ~WiFiSetup();

        /** Function to initialise WiFiSetup */
        void init();

        /** Scan for WiFi networks, print the networks and create a network
         *  vector
         *  \return Number of WiFi networks discovered
         */
        int scan_networks();

        /** Create the vector of NetworkData structs
         *  \param number_networks  Number of networks discovered
         */
        void create_network_vector(int number_networks);

        /** Print the data contained within the _network_data_vector vector */
        void print_networks();

        /** Print the networks in a more simple format */
        void print_networks_simple();

        /** Translates the date encyryption type from the type defined in the 
         *  WiFi class to a string
         *  \param encyrption_type  Encryption type
         *  \return String containing encryption type
         */
        String translate_encryption_type(wifi_auth_mode_t encryption_type);

        /** Refreshes WiFi networks when 'r' pressed in terminal */
        void refresh_networks();

        /** Allows the user to enter a number into the serial console
         * \return Number that the user has entered
         */
        int enter_number();

        /** Converts the dBm signal strength into a verbose signal strength
         * (stored using VerboseSigStrength enum type)
         * \param sig_strength_dbm  Signal strength in dBm
         * \return Signal strength in VerboseSigStrength enum type
         */
        VerboseSigStrength dbm_to_verbose_signal(long sig_strength_dbm);

        /** Prints the verbose signal strength over serial
         * \param sig_strength_verbose  Verbose signal strength
         */
        void print_verbose_signal(VerboseSigStrength sig_strength_verbose);

        /** Allows the user to select the network they wish to connect to 
         * \return Number of network to connect to (correspnds to position in
         *         _network_data_vector)
        */
        int select_network();

        /** Allows the user to enter the WPA passphrase of the WiFi network */
        void enter_passphrase();

        /** Connection wizard for WiFi network */
        void connect_to_network();

        /** Return the selected SSID
         * \return String containing SSID
         */
        String get_ssid();

        /** Return the WPA passphrase
         * \return String containing WPA passphrase
         */
        String get_wpa_passphrase();

        /** Allows the user to enter an IP address and converts the IP to an
         * unsigned long value (32 bits)
         * \return IP address in unsigned long
         */
        unsigned long input_ip_address();

        /** Allows the user to set up a static IP address with optional DNS */
        void static_ip_dns();

        /** Receives several characters from the serial monitor and passes them
         * to an array of chars- based on the method in
         * https://forum.arduino.cc/index.php?topic=396450.0
         * \param char_array    Array of chars
         * \param length_char   Length of char array
         * \return True when data finished receiving, false otherwise
         */
        bool read_chars_serial(char* char_array, int length_char);

        /** Starts the ESP32 hardware timer to end at the time stated
         * \param time          Time in seconds
         */
        void start_timeout_timer(uint16_t time);

        /** Sets timeout flag when interrupt triggered */
        static void on_timeout_timer();

        /** Ends the timeout timer */
        static void end_timeout_timer();

        /** Gets a single character from the serial buffer and returns it
         * \return Character from serial buffer
         */
        char get_char();

        /** Main setup wizard for setting up WiFi connections */
        void setup_wizard();

        /** Print the advanced network view and wait for user to press
         * the space bar to exit */
        void show_adv_network_view();

        /** Display 'Establishing connection' prompt while connecting */
        void display_establishing_conn_prompt();

        /** Create a value for the ConnectionType enum
         * \return ConnectionType enum
         */
        ConnectionType create_conn_type_value();

        /** Save the WiFi settings to NVS if the connection is successful */
        void save_settings_to_nvs();

        /** Attempt to connect using settings stored in NVS
         * \return True when attempted, false otherwise
         */
        bool connect_using_nvs_settings();

        /** Begin WiFi using NVS parameters */
        void begin_nvs();

        /** Configure the DNS using NVS settings */
        void config_dns_nvs();

        /** Display prompt for user to skip NVS connection
         * \return True to skip NVS connection, false otherwise
         */
        bool skip_nvs_connection();

        /** Load network settings from ROM and attempt to connect
         * \return True if connection successful, false if not
         */
        bool load_connect();

        /** Allows the user to re-configure the network on boot if settings
         *  are saved 
         * \return True if networks need reconfiguring, false otherwise
         * */
        bool reconfig_prompt();

        /** Iterates through the network vector to see whether an SSID exists
         * \param ssid  SSID to check
         * \return True if SSID found, false if not found
         */
        bool check_ssid_exists_vector(String ssid);

    private:
        // Hardware timer - used for connection timeout
        static hw_timer_t * _timer;

        // Network data vector
        std::vector<NetworkData> _network_data_vector;

        // Flag to state whether connection has been attempted using the settings
        // stored in NVS
        bool _attempt_connect_nvs;
        
        // SSID storage for connection
        String _selected_ssid;

        // WPA passphrase
        char _wpa_passphrase[64];

        // Length of WPA passphrase
        int _length_wpa_pass;

        // Number of selected network
        int _selected_network;

        // WiFi connection status
        wl_status_t _conn_status;

        // Flag for WPA encryption
        bool _wpa_encryption;
    
        // Flag for static IP/DHCP - true for static IP
        bool _use_static_ip;

        // Flag for using custom DNS
        bool _custom_dns;

        // Static IP address
        unsigned long _static_ip;

        // Gateway IP address
        unsigned long _gateway_ip;

        // Subnet mask
        unsigned long _subnet_mask;

        // DNS server 1
        unsigned long _dns_server_1;

        // DNS server 2
        unsigned long _dns_server_2;

        // Enum used to save connection type
        ConnectionType _conn_type;

        
};

#endif