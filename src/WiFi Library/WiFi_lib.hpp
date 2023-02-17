#ifndef WIFI_LIB
#define WIFI_LIB

#include <WiFi.h>

#define DEBUG

class WiFiManager{
protected:
	char WIFI_SSID[128];
	char WIFI_PASS[128];


public:
	WiFiManager(char* WIFI_SSID, char* WIFI_PASS);
	void reconnect();
	void loop() { this -> reconnect(); }

	IPAddress 	getLocalIP(){ return WiFi.localIP(); }
	IPAddress 	getSubnet(){ return WiFi.subnetMask(); }
	String 		getLocalIP_string(){return this->getLocalIP().toString();}
};

#endif