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

public:
	void addClient(Clients* client=NULL);

	void loop();
	void loopClients(Manager* manager);
};

#endif