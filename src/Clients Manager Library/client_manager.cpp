#include "client_manager.hpp"

using CM = ClientManager;

void CM::addClient(Clients* client){
	
	#ifdef DEBUG
		Serial.println("Adding client \"" + client -> getName() + "\" to manager");
	#endif

	if(this -> manager == NULL){
		this -> manager = (Manager*) malloc(sizeof(Manager));
		this -> manager -> client = client;
		this -> manager -> next = NULL;
	}else{
		Manager* temp = manager;

		while(temp -> next != NULL) temp = temp -> next;

		temp -> next = (Manager*) malloc(sizeof(Manager));
		temp -> next -> client = client;
		temp -> next -> next = NULL;
	}
}

void CM::loopClients(Manager* manager){
	if(manager == NULL) return;

	Clients* client = manager -> client;

	if(!client -> getClient() -> connected()){
		Clients::TOPICS* topic = client -> TOPIC;
		client -> reconnect();
		while(topic != NULL){
			client -> client -> subscribe(topic -> TOPIC);

			topic = topic -> next;
		}
	}

	client -> client -> loop();

	#ifdef DEBUG
		Serial.flush();
	#endif

	this -> loopClients(manager -> next);
}

void CM::loop(){
	this -> loopClients(this -> manager);
}