#include "clients.hpp"

Clients* Clients::pointer 			= NULL;

char Clients::START_MESSAGE[128] 	= "start";
char Clients::STOP_MESSAGE[128] 	= "stop";

void Clients::receiveMessage(const MqttClient*/*src*/, const Topic& topic, 
						const char* payload, size_t /*length*/){
	// DO SOMETHING
	#ifdef DEBUG
		Serial.println("New message with topic: " + String(topic.c_str()));
		Serial.println("Client " + Clients::getPointer() -> getName() + " is processing message \"" + String(payload) + "\"\n");
	#endif

	char* message = (char*) malloc(sizeof(char) * 128);
	toLowercase(payload, message);

	if(!strcmp(message, Clients::getStartMessage())){
		#ifdef DEBUG
			Serial.println("\t # Waking up: " + Clients::getPointer() -> getMAC_ADDR());
		#endif
		Clients::getPointer() -> wakeUP();
	}else if(!strcmp(message, Clients::getStopMessage())){
		#ifdef DEBUG
			Serial.println("\t # Putting to sleep: " + Clients::getPointer() -> getName());
		#endif
		Clients::getPointer() -> sleep();
	}
}

void toLowercase(const char* payload, char* message){
	int i = 0;
	while(i < 127 && payload[i] != '\0'){
		if(payload[i] >= 'A' && payload[i] <= 'Z') {
			message[i] = payload[i] + ('a' - 'A');
		}else{
			message[i] = payload[i];
		}

		i++;
	}

	message[i] = '\0';
}

Clients::Clients(String SERVER_IP_ADDR, int SERVER_PORT, String name){
	this -> client 				= new MqttClient();
	this -> TOPIC 				= NULL;
	this -> SERVER_PORT 		= 1883;
	this -> SERVER_IP_ADDR[0] 	= '\0';

	strcpy(this -> SERVER_IP_ADDR, SERVER_IP_ADDR.c_str());
	strcpy(this -> name, name.c_str());
	this -> SERVER_PORT = SERVER_PORT;

	#ifdef DEBUG
		Serial.println("Created client: " + String(this -> name));
	#endif

	this -> updatePointer();
	this -> client -> connect(this -> SERVER_IP_ADDR, this -> SERVER_PORT);
		
	this -> client -> setCallback(Clients::receiveMessage);
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
	this -> client -> publish(this -> getName().c_str(), "stop");
}