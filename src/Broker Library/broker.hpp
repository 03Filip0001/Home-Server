#ifndef BROKER
#define BROKER

#include "TinyMqtt.h"

//#define DEBUG

class Broker{
protected:
	int PORT;
	MqttBroker* broker;

public:
	Broker(int PORT=1883);
	void loop() {this -> broker -> loop(); }

	int getPORT(){ return this -> PORT; }
};

#endif