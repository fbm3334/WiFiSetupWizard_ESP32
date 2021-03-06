// Example code for using the WiFiSetupWizard_ESP32 library using PlatformIO
// Code by Finn Beckitt-Marshall, June 2020

#include <Arduino.h>
#include <WiFiSetup.h> // Include <WiFiSetup.h>

WiFiSetup wsetup;

void setup() {
  // Initiate the serial connection to view terminal output
  Serial.begin(115200);
  // Initialise WiFiSetup
  wsetup.init();
  while (WiFi.status() != WL_CONNECTED) {
    wsetup.setup_wizard();
  }

  // Print the IP address when connected
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
}

void loop() {

}


