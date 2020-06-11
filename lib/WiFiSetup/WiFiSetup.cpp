#include <WiFiSetup.h>

// Initialisation of static variables
bool WiFiSetup::connect_timeout = false;

hw_timer_t * WiFiSetup::timer = NULL;

WiFiSetup::WiFiSetup() {

}

WiFiSetup::~WiFiSetup() {

}

void WiFiSetup::init() {
    // Automatically defaults to DHCP
    _use_static_ip = false;
    // Initialise hardware timer to null
    timer = NULL;
    // Set timeout flag to false
    connect_timeout = false;
    // Initialise preferences
    prefs.begin("WiFiSettings", false);

    // Check whether the SSID field is empty by checking string length
    if (prefs.getString("SSID", "").length() == 0) {
        Serial.println("SSID not stored on ESP32 ROM");
    } else {
        /* Serial.println(prefs.getString("SSID", ""));
        Serial.println(prefs.getString("Pass", ""));
        Serial.println(prefs.getBool("isWPA")); */
    }
}

int WiFiSetup::scan_networks() {
    // Scan the networks and print the number of networks found
    int number_networks = WiFi.scanNetworks();
    Serial.print("WiFi Status");
    Serial.println(WiFi.status());

    Serial.print("Number of networks found: ");
    Serial.println(number_networks);

    // Create the network vector
    create_network_vector(number_networks);
    return number_networks;
}

String WiFiSetup::translate_encryption_type(wifi_auth_mode_t encryption_type) {
    // Switch-case loop used
    switch (encryption_type) {
        case (WIFI_AUTH_OPEN):
            return "Unencrypted";
        case (WIFI_AUTH_WEP):
            return "WEP";
        case (WIFI_AUTH_WPA_PSK):
            return "WPA-PSK";
        case (WIFI_AUTH_WPA2_PSK):
            return "WPA2-PSK";
        case (WIFI_AUTH_WPA_WPA2_PSK):
            return "WPA/WPA2-PSK";
        case (WIFI_AUTH_WPA2_ENTERPRISE):
            return "WPA2 Enterprise";
        default:
            return "Unknown encryption type";
    }
}

void WiFiSetup::create_network_vector(int number_networks) {
    // Create an instance of the NetworkData struct to write network data to
    NetworkData current_network;
    
    // For loop to add data to NetworkData struct and append this to the vector
    for (int i = 0; i < number_networks; i++) {
        current_network.network_ssid = WiFi.SSID(i);
        current_network.network_signal_strength = WiFi.RSSI(i);
        current_network.signal_verbose = dbm_to_verbose_signal(WiFi.RSSI(i));
        current_network.network_mac = WiFi.BSSIDstr(i);
        current_network.network_type_libform = WiFi.encryptionType(i);
        current_network.network_type = translate_encryption_type(WiFi.encryptionType(i));
        current_network.network_chan = WiFi.channel(i);
        // Append this to the end of the vector
        _network_data_vector.push_back(current_network);
    }
}

void WiFiSetup::print_networks() {
    // Create the iterator to iterate through the vector
    std::vector<NetworkData>::iterator it;
    // Iterate through the vector in order to print the networks
    for (it = _network_data_vector.begin(); it != _network_data_vector.end(); ++it) {
        Serial.println("----------------------------------------");
        Serial.print("SSID:                     ");
        Serial.println((*it).network_ssid);
        Serial.print("Signal strength (dBm):    ");
        Serial.println((*it).network_signal_strength);
        Serial.print("Signal strength:          ");
        print_verbose_signal((*it).signal_verbose);
        Serial.println("");
        Serial.print("MAC address:              ");
        Serial.println((*it).network_mac);
        Serial.print("Network encryption type:  ");
        Serial.println((*it).network_type);
        Serial.print("Channel:                  ");
        Serial.println((*it).network_chan);
    }
}

void WiFiSetup::print_networks_simple() {
    // Create the iterator to iterate through the vector
    std::vector<NetworkData>::iterator it;
    // First network is number 1
    int network_count = 1;
    // Print initial line for network data
    Serial.println("Num: SSID:                            Sig:");
    // Create char arrays to print out
    char network_num[3];
    char network_ssid[33]; // 33 chars long due to null terminator
    char network_ssid_pad[32]; // 32 l
    // Iterate through the vector in order to print the networks in tabular form
    for (it = _network_data_vector.begin(); it != _network_data_vector.end(); ++it) {
        sprintf(network_num, "%-3i  ", network_count);
        Serial.print(network_num);
        ((*it).network_ssid).toCharArray(network_ssid, 32);
        sprintf(network_ssid_pad, "%-32s ", network_ssid);
        Serial.print(network_ssid_pad);
        print_verbose_signal((*it).signal_verbose);
        Serial.println(""); // Start a new line
        network_count++; // Increment the network counter
    }
}

void WiFiSetup::refresh_networks() {
    // Clear the network vector
    _network_data_vector.clear();
    Serial.println("Networks cleared.");
    // Rescan and print WiFi networks to the terminal
    scan_networks();
    
    // Send an ASCII form feed to clear terminal data
    //char delete_term = 12;
    //Serial.print(delete_term);
    print_networks_simple();
}

int WiFiSetup::enter_number() {
    bool data_ready = false;
    char num_array[6]; // Max int is 65536 so 6 characters inc. null terminator
    while (data_ready == false) {
        data_ready = read_chars_serial(num_array, 6);
    }
    data_ready = false;
    int number_entered = atoi(num_array);
    return number_entered;
}

VerboseSigStrength WiFiSetup::dbm_to_verbose_signal(long sig_strength_dbm) {
    /* Range used for dBm to verbose values
     * 0 to -50dBm      Excellent
     * -51 to -60dBm    Good
     * -61 to -70dBm    Fair
     * < -70dBm           Weak
     */
    if (sig_strength_dbm < -70) {
        return Weak;
    } else if (sig_strength_dbm < -61) {
        return Fair;
    } else if (sig_strength_dbm < -51) {
        return Good;
    } else {
        return Excellent;
    }
}

void WiFiSetup::print_verbose_signal(VerboseSigStrength sig_strength_verbose) {
    // Case loop to print verbose signal
    switch (sig_strength_verbose) {
        case Excellent:
            Serial.print("OOOO");
            break;
        case Good:
            Serial.print("OOO.");
            break;
        case Fair:
            Serial.print("OO..");
            break;
        case Weak:
            Serial.print("O...");
            break;
    }
}

int WiFiSetup::select_network() {
    int network_num = -1;
    // While loop used to validate the input (if less than 0 or greater than
    // length of network vector, will re-run
    while ((network_num <= 0) || (network_num > _network_data_vector.size())) {
        // User inputs a number of the network they want to connect to
        Serial.print("Type in the network number and press Enter to confirm: ");
        network_num = enter_number();
        Serial.print("Network number selected: ");
        Serial.println(network_num);
    }
    // Access the SSID given by network_num (stored in _network_data_vector) and print it
    _selected_ssid = _network_data_vector[network_num - 1].network_ssid;
    Serial.print("Selected SSID: ");
    Serial.println(_selected_ssid);
    return (network_num - 1); // Network number - 1 returned due to array refs
}

void WiFiSetup::enter_passphrase() {
    // Print message to enter passphrase
    Serial.print("Enter network passphrase: ");

    bool data_ready = false;
    while (data_ready == false) {
        data_ready = read_chars_serial(_wpa_passphrase, 64);
    }
    data_ready = false;
}

void WiFiSetup::connect_to_network() {
    // Initialise hardware timer to null
    timer = NULL;
    // Set timeout flag to false
    connect_timeout = false;
    _accepted_encryption = false;
    // Select the network from the list
    _selected_network = select_network();
    Serial.println("Connecting to network...");

    String encryption_type = _network_data_vector[_selected_network].network_type;

    if (encryption_type == "Unencrypted") {
        Serial.println("Selected network is open, no passphrase is required.");
        WiFi.begin(_selected_ssid.c_str(), NULL, 0, NULL, true);
        _accepted_encryption = true;
    } else if (encryption_type == "WEP" || encryption_type == "WPA2 Enterprise") {
        Serial.println("Network type is not currently supported.");
    } else {
        _wpa_encryption = true;
        enter_passphrase();
        WiFi.begin(_selected_ssid.c_str(), _wpa_passphrase, 0, NULL, true);
        _accepted_encryption = true;
        start_timeout_timer(10);
    }

    /* if (_accepted_encryption == true) {
        start_timeout_timer(10);
    } */
    
    while ((WiFi.status() != WL_CONNECTED) && (_accepted_encryption == true) &&
            (connect_timeout == false)) {
        delay(1000);
        Serial.println("Establishing connection to network...");
    }
    // If the connection is successful, save settings to ROM
    if (WiFi.status() == WL_CONNECTED) {
        save_to_rom();
        prefs.end();
    }
}

String WiFiSetup::get_ssid() { return _selected_ssid; }

String WiFiSetup::get_wpa_passphrase() { return _wpa_passphrase; }

IPAddress WiFiSetup::input_ip_address() {
    // Defining octet variables
    uint8_t octet_1;
    uint8_t octet_2;
    uint8_t octet_3;
    uint8_t octet_4;

    // IP address is 16 chars long (incl null terminator)
    char ip_address_string[LENGTH_IP_CHAR];
    ip_address_string[0] = 0; // Zero the first element to clear array

    bool data_ready = false;
    int num_items = 0;
    while (num_items < 4) {
        while (data_ready == false) {
            data_ready = read_chars_serial(ip_address_string, LENGTH_IP_CHAR);
            // Using sscanf to read the IP address
        }
        data_ready = false;
        num_items = sscanf(ip_address_string, "%hhu.%hhu.%hhu.%hhu", &octet_1, 
                                &octet_2, &octet_3, &octet_4);
        if (num_items < 4) { 
            Serial.println("Invalid IP address entered. Please re-enter the IP address: ");
        }
    }

    #ifdef PRINT_IP
        Serial.println(ip_address_string);
        Serial.println(num_items);
        Serial.println(octet_1);
        Serial.println(octet_2);
        Serial.println(octet_3);
        Serial.println(octet_4);
    #endif

    return IPAddress(octet_1, octet_2, octet_3, octet_4);
}

void WiFiSetup::static_ip_dns() {
    // Get the static IP, gateway IP and subnet mask
    Serial.println("Enter static IP address: ");
    _static_ip = input_ip_address();
    Serial.print("Enter gateway IP address: ");
    _gateway_ip = input_ip_address();
    Serial.print("Enter subnet mask: ");
    _subnet_mask = input_ip_address();
    
    // Ask the user whether they want to use a custom DNS
    Serial.println("Press 'd' to use custom DNS or 'n' to skip");
    char received_char;
    bool valid_char = false;
    while (valid_char == false) {
        received_char = get_char();
        if (received_char == 'd' || received_char == 'n') {
            valid_char = true;
        }
    }
    // Interpret the received character and do the required action
    if (received_char == 'd') {
        Serial.println("Enter DNS server 1: ");
        _dns_server_1 = input_ip_address();
        Serial.println("Enter DNS server 2: ");
        _dns_server_2 = input_ip_address();
        WiFi.config(_static_ip, _gateway_ip, _subnet_mask, _dns_server_1, 
                    _dns_server_2);
    } else if (received_char == 'n') {
        WiFi.config(_static_ip, _gateway_ip, _subnet_mask);
    }
}

bool WiFiSetup::read_chars_serial(char* char_array, int length_char) {
    static byte ndx = 0;
    char end_marker = 13; // Carriage return
    char recv_char;

    while (Serial.available() > 0) {
        recv_char = Serial.read();

        if (recv_char != end_marker) {
            //Serial.print(recv_char);
            char_array[ndx] = recv_char;
            ndx++;
            if (ndx >= length_char) {
                ndx = length_char - 1;
            }
        // Backspace
        } else if (recv_char == 8) {
            Serial.print(recv_char);
            ndx--; // Decrement ndx by 1
            char_array[ndx] = 0; // Zero array at new ndx pos
        } else {
            char_array[ndx] = '\0'; // Terminate the string
            ndx = 0;
            Serial.println(char_array);
            return true;
        }
    }
    return false;
}

void WiFiSetup::start_timeout_timer(uint16_t time) {
    // Base clock is 80MHz, so dividing clock by 80
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &WiFiSetup::on_timeout_timer, true);
    timerAlarmWrite(timer, (1000000 * time), true);
    timerAlarmEnable(timer);
}

void WiFiSetup::on_timeout_timer() {
    connect_timeout = true;
    //Serial.println("Timeout");
    end_timeout_timer();
}

void WiFiSetup::end_timeout_timer() {
    timerEnd(timer);
    timer = NULL;
}

char WiFiSetup::get_char() {
    char return_char = 0;
    if (Serial.available() > 0) {
        return_char = Serial.read();
    }
    return return_char;
}

void WiFiSetup::setup_wizard() {
    // Clear the screen
    Serial.print("\f");
    // Print introduction to setup wizard
    Serial.println("WiFi Setup Wizard for ESP32");
    Serial.println("Developed by Finn Beckitt-Marshall, 2020");

    // Refresh the networks
    refresh_networks();


    // User prompt - 'a' for advanced view, 'd' to connect to a network using
    // DHCP and 's' to connect to a network using a static IP
    Serial.println("Connection Options:\na - Advanced network view");
    Serial.println("d - Connect using DHCP\ns - Connect using static IP");
    Serial.println("r - Rescan networks");
    char received_char;
    bool valid_char = false;
    while (valid_char == false) {
        received_char = get_char();
        if (received_char == 'a' || received_char == 'd' || received_char == 's'
            || received_char == 'r') {
            valid_char = true;
        }
    }

    // Do the appropriate operation based on response
    if (received_char == 'a') {
        show_adv_network_view();
    } else if (received_char == 'd') {
        connect_to_network();
    } else if (received_char == 's') {
        _use_static_ip = true;
        static_ip_dns();
        connect_to_network();
    } else if (received_char == 'r') {
        // All doing 'r' needs to do is clear the screen - the while loop will
        // refresh the screen
    }
}

void WiFiSetup::show_adv_network_view() {
    // Print the advanced network view
    print_networks();
    Serial.println("Press space bar to exit.");
    // Wait for the space bar to be pressed
    char received_char;
    bool valid_char = false;
    while (valid_char == false) {
        received_char = get_char();
        if (received_char == ' ') {
            valid_char = true;
        }
    }
}

void WiFiSetup::save_to_rom() {
    prefs.begin("WiFiSettings", false);
    Serial.println("Saving WiFi settings to ROM...");
    prefs.putString("SSID", _selected_ssid);
    if (_wpa_encryption == true) { prefs.putString("Pass", _wpa_passphrase); }
    prefs.putBool("is_WPA", _wpa_encryption);
    prefs.end();
}

bool WiFiSetup::load_connect() {
    // Show reconfig prompt
    if (reconfig_prompt()) {
        return false;
    }
    // Initialise hardware timer to null
    timer = NULL;
    // Set timeout flag to false
    connect_timeout = false;
    // Get the variables from the ROM
    _selected_ssid = prefs.getString("SSID", "");
    _wpa_encryption = prefs.getBool("is_WPA");
    Serial.print("SSID: ");
    Serial.println(_selected_ssid);
    Serial.print("WPA: ");
    Serial.println(_wpa_encryption);
    Serial.print("Pass: ");
    Serial.println(prefs.getString("Pass", ""));
    if (_wpa_encryption == true) { 
        (prefs.getString("Pass", "")).c_str();
        WiFi.begin(_selected_ssid.c_str(), prefs.getString("Pass", "").c_str(),
                   0, NULL, true);
    } else {
        WiFi.begin(_selected_ssid.c_str(), NULL, 0, NULL, true);
    }
    
    // Attempt to connect using the stored variables
    start_timeout_timer(10);
    Serial.println("Establishing connection to network");
    while ((WiFi.status() != WL_CONNECTED) && (connect_timeout == false)) {
        delay(1000);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.print(WiFi.localIP());
        return true;
        
    }
    prefs.end();
    return false;
}

bool WiFiSetup::reconfig_prompt() {
    // Print the reconfigure prompt text
    Serial.println("Press 'r' to reconfigure networks...");
    // Initialise hardware timer to null
    timer = NULL;
    // Set timeout flag to false
    connect_timeout = false;
    // Start timeout timer - 5 seconds
    start_timeout_timer(5);
    char received_char;
    bool reconfig = false;
    while (connect_timeout == false && reconfig == false) {
        // Capture serial input
        received_char = get_char();
        if (received_char == 'r') {
            reconfig = true;
        }
    }
    return reconfig;
}