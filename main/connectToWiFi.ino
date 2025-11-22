//all connection passwords taken from wifipass.h
void connect_to_Wifi() {
    Serial.print("Connecting to ");
    Serial.println(SSID_NAME);

    WiFi.begin(SSID_NAME, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    
}

