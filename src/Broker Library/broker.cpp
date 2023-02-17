#include "broker.hpp"

Broker::Broker(int PORT){
	this -> PORT = PORT;
	broker = new MqttBroker(this -> PORT);

	#ifdef DEBUG
		Serial.println("Starting MQTT Broker on port " + String(this -> PORT));
	#endif
	this -> broker -> begin(); 
}