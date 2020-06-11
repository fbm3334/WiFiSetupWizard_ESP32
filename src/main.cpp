#include <Arduino.h>
#include <WiFiSetup.h>

WiFiSetup wsetup;

void setup() {
  // Initiate the serial connection to view terminal output
  Serial.begin(115200);
  // Initialise WiFiSetup
  wsetup.init();
  // Use a while loop to try connecting while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED) {
    wsetup.setup_wizard();
  }
  // Print the IP address when connected
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
}

void loop() {

}

