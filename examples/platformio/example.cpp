// Example code for using the WiFiSetupWizard_ESP32 library using PlatformIO
// Code by Finn Beckitt-Marshall, June 2020

#include <Arduino.h>
#include <WiFiSetup.h> // Include <WiFiSetup.h>

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


