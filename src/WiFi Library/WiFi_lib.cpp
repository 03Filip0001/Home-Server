#include "WiFi_lib.hpp"

WiFiManager::WiFiManager(char* WIFI_SSID, char* WIFI_PASS){
	strcpy(this -> WIFI_SSID, WIFI_SSID);
	strcpy(this -> WIFI_PASS, WIFI_PASS);

	#ifdef DEBUG
		Serial.println("Connecting to WiFi: " + String(this -> WIFI_SSID));
	#endif

	WiFi.mode(WIFI_STA);
	this -> reconnect();

	while (WiFi.status() != WL_CONNECTED) {
	    #ifdef DEBUG
			Serial.print(".");
		#endif
	    delay(500);
  	}

  	#ifdef DEBUG
		Serial.println(".");
		Serial.println("Connected to " + String(this -> WIFI_SSID) + " with IP address: " + this -> getLocalIP_string());
	#endif
}

void WiFiManager::reconnect(){
	if(WiFi.status() != WL_CONNECTED){

		#ifdef DEBUG
			Serial.println("Reconnecting to WiFi: " + String(this -> WIFI_SSID));
		#endif

		WiFi.disconnect();
		WiFi.begin(this -> WIFI_SSID, this -> WIFI_PASS);
	}
}