#include "clients.hpp"

char Clients::START_MESSAGE[128] 	= "start";
char Clients::STOP_MESSAGE[128] 	= "stop";

Clients::Clients(String SERVER_IP_ADDR, int SERVER_PORT, String name){
	this -> client 				= new MqttClient(name.c_str());
	this -> TOPIC 				= NULL;
	this -> SERVER_PORT 		= 1883;
	this -> SERVER_IP_ADDR[0] 	= '\0';

	strcpy(this -> SERVER_IP_ADDR, SERVER_IP_ADDR.c_str());
	strcpy(this -> name, name.c_str());
	this -> SERVER_PORT = SERVER_PORT;

	#ifdef DEBUG
		Serial.println("Created client: " + String(this -> name));
	#endif

	this -> client -> connect(this -> SERVER_IP_ADDR, this -> SERVER_PORT);

	this -> addTopic("main");
}

void Clients::addTopic(char* TOPIC){

	#ifdef DEBUG
		Serial.println("Adding topic \"" + String(TOPIC) + "\" to client " + String(this -> name));
	#endif

	if(this -> TOPIC == NULL){
		this -> TOPIC = (TOPICS*) malloc(sizeof(TOPICS));

		strcpy(this -> TOPIC -> TOPIC, TOPIC);
		this -> TOPIC -> next = NULL;
	}else{
		TOPICS* temp = this -> TOPIC;

		while(temp -> next != NULL) temp = temp -> next;

		temp -> next = (TOPICS*) malloc(sizeof(TOPICS));
		strcpy(temp -> next -> TOPIC, TOPIC);
		temp -> next -> next = NULL;
	}

	this -> client -> subscribe(TOPIC);

}

void Clients::setMAC_ADDR(char* MAC_ADDR) {
	
	#ifdef DEBUG
		Serial.println("Setting MAC address for client " + String(this -> name) + ": " + String(MAC_ADDR));
	#endif

	WakeOnLAN_class::setMAC_ADDR(MAC_ADDR);
}

void Clients::sleep(){
	Serial.println("Putting machine down to sleep with MAC address: " + String(MAC_ADDR));

	this -> client -> publish(this -> getName().c_str(), "stop");
}