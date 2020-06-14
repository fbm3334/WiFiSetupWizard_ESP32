// Example code for using the WiFiSetupWizard_ESP32 library with the Arduino IDE
// Code by Finn Beckitt-Marshall, June 2020

// To use the library, copy the /lib/WiFiSetup folder from the repository and
// paste it into your Arduino libraries folder:
// Typical locations:
// - Windows: C:\Users\your_user\My Documents\Arduino\libraries
// - macOS: /Users/your_user/Documents/Arduino/libraries
// - Linux: /home/your_user/Arduino/libraries
// Then, restart your Arduino IDE and the library should appear in the
// Sketch/Include Library menu.

#include <WiFiSetup.h>

WiFiSetup wsetup;

// The entirety of the code runs within void setup().
void setup() {
  // Initiate the serial connection to view terminal output
  Serial.begin(115200);
  // Initialise WiFiSetup
  wsetup.init();
  // Run the setup wizard while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED) {
    wsetup.setup_wizard();
  }
  // Print the IP address when connected
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}
