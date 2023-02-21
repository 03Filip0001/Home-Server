#ifndef CLIENTS_HPP
#define CLIENTS_HPP

#include "TinyMqtt.h"
#include "./../WakeOnLAN Library/wol.hpp"

//#define DEBUG

extern void toLowercase(const char*, char*);

class Clients : public WakeOnLAN_class {

friend class ClientManager;

protected:

	static char START_MESSAGE[128];
	static char STOP_MESSAGE[128];

	struct topic_struct{
		char TOPIC[128];
		struct topic_struct *next;
	};
	typedef struct topic_struct TOPICS;

	MqttClient* client;

	char 	SERVER_IP_ADDR[16];
	int 	SERVER_PORT;
	char	name[128];

	TOPICS* TOPIC;

	void sleep();
	void reconnect() { this -> client -> connect(this -> SERVER_IP_ADDR, this -> SERVER_PORT); }

	static char*	getStartMessage() 	{ return START_MESSAGE; }
	static char*	getStopMessage() 	{ return STOP_MESSAGE; }

public:
	Clients(String SERVER_IP_ADDR="", int SERVER_PORT=1883, String name="test");

	void addTopic(char* TOPIC);
	void sendMessage(char* topic, char* message);

	void setMAC_ADDR(char* MAC_ADDR) override;

	String getName() {return String(this -> name); }

	MqttClient* getClient() { return this -> client; }
};

#endif