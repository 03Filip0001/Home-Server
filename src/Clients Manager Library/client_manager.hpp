#ifndef CLIENT_MANAGER
#define CLIENT_MANAGER

#include "./../Clients Library/clients.hpp"

//#define DEBUG

class ClientManager{
protected:
	typedef struct clients_struct{
		Clients* client;
		struct clients_struct *next;
	}Manager;

	Manager* manager = NULL;

	void cicleClients(const char* id, const char* payload, char all=false);

public:

	using Callback = void (*)(const MqttClient* source, const Topic& topic, const char* payload, size_t payload_length);

	void setCallbacks(Callback fun);
	void addClient(Clients* client=NULL);

	void loop();
	void loopClients(Manager* manager);

	void findClients(const MqttClient* client_id, const char* topic, const char* payload);
};

#endif