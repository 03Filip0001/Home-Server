#include "wol.hpp"

using WOL_CL = WakeOnLAN_class;

WOL_CL::WakeOnLAN_class(){
	this -> WOL = new WakeOnLan(this -> UDP);
	this -> WOL -> calculateBroadcastAddress(wifi -> getLocalIP(), 
												wifi -> getSubnet());
}

void WOL_CL::wakeUP(){
	this -> WOL -> sendMagicPacket(this -> MAC_ADDR);

	#ifdef DEBUG
		Serial.println("Waking up machine with MAC address: " + String(this -> MAC_ADDR));
	#endif
}