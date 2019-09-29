/*
   WiFi.cpp

*/

#include "Wifi.h"

void Wifi::begin() {
  WiFi.begin (WIFI_SSID, WIFI_PSW);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print (".");
  }

#ifdef DEBUG
  Serial.print("\n");
  Serial.print("\nConnected to : "); Serial.print(WIFI_SSID);
  Serial.print("\nIP address :   "); Serial.print(WiFi.localIP());
  Serial.print("\n\n");
#endif

  if (!MDNS.begin(MDNS_NAME)) {
    Serial.print("Error setting up MDNS responder!\n");
    while (1)
      delay(1000);
  }

#ifdef DEBUG
  Serial.print("MDNS responder started @ http://");
  Serial.print(MDNS_NAME);
  Serial.print(".local");
  Serial.print("\n\n");
#endif
}
