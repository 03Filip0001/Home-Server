#ifndef WOL_HPP
#define WOL_HPP

#include <WiFiUdp.h>
#include <WakeOnLan.h>

#include "./../WiFi Library/WiFi_lib.hpp"

//#define DEBUG

extern WiFiManager* wifi;

class WakeOnLAN_class{
protected:
	WiFiUDP UDP;
	WakeOnLan* WOL;
	char MAC_ADDR[18];


public:
	WakeOnLAN_class();
	void wakeUP();

	virtual void setMAC_ADDR(char* MAC_ADDR){ strcpy(this -> MAC_ADDR, MAC_ADDR); }
	String getMAC_ADDR() { return String(this -> MAC_ADDR); }
};

#endif