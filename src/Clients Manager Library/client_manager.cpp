#include "client_manager.hpp"

using CM = ClientManager;

void CM::cicleClients(const char* id, const char* payload, char all){
	Manager* manager = this -> manager;

	while(manager != NULL){
		if(all && !strcmp(payload, manager -> client -> getStartMessage())){
			manager -> client -> wakeUP();
		}else if(all && !strcmp(payload, manager -> client -> getStopMessage())){
			manager -> client -> sleep();
		}else if(!all){
			if(!strcmp((manager -> client -> getClient() -> id()).c_str()	, id)){
				if(!strcmp(payload, manager -> client -> getStartMessage())){
					manager -> client -> wakeUP();
				}else if(!strcmp(payload, manager -> client -> getStopMessage())){
					manager -> client -> sleep();
				}
			}
		}

		manager = manager -> next;
	}
}

void CM::findClients(const MqttClient* client_id, const char* topic, const char* payload){
	if(!strcmp("main", topic)){
		cicleClients((client_id -> id()).c_str(), payload, true);
	}else{
		cicleClients((client_id -> id()).c_str(), payload);
	}
}

void CM::setCallbacks(Callback fun){
	Manager* temp = this -> manager;

	Serial.print("Setting callback for clients: ");

	while(temp != NULL){
		temp -> client -> getClient() -> setCallback(fun);
		Serial.print(temp -> client -> getName());
		Serial.print(", ");
		temp = temp -> next;
	}

	Serial.println();
}

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