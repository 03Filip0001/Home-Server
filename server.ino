#include "server.hpp"

#define EEPROM_SIZE 1

#define WIFI_SSID "TP-LINK_GOLD"
#define WIFI_PASS "slobodno"

WiFiManager* wifi;

Broker* broker;

Clients* server;
Clients* FILIP_PC;

ClientManager* manager;

void mess(const MqttClient* client , const Topic& topic, const char* payload, size_t length ){
    // DO SOMETHING
    Serial.print("#############");

    Serial.print((unsigned int)client, HEX);
    Serial.print("   :::   ");
    Serial.print((unsigned int)server -> getClient(), HEX);
    Serial.print("   :::   ");
    Serial.print((client -> id()).c_str());
    Serial.print("   :::   ");
    Serial.print((server -> getClient() -> id()).c_str());
    Serial.print("   ");
    
    Serial.println("#############");

    manager -> findClients(client, topic.c_str(), payload);
    
}

void setup(){
	// ESP32 communication and memory
	Serial.begin(115200);
	EEPROM.begin(EEPROM_SIZE);

	// ESP32 WiFi communication
    wifi 		= new WiFiManager(WIFI_SSID, WIFI_PASS);

	// MQTT broker
	broker      = new Broker(1883);

	// Create clients
	server 		= new Clients(wifi -> getLocalIP_string(), broker -> getPORT(), String("server"));
	//FILIP_PC 	= new Clients(wifi -> getLocalIP_string(), broker -> getPORT(), String("FILIP_PC"));

	server 		-> setMAC_ADDR("00:30:05:ab:77:6a");
	//FILIP_PC 	-> setMAC_ADDR("b4:2e:99:c9:72:a0");

	server 		-> addTopic("main/server");
	//FILIP_PC 	-> addTopic("main/FILIP_PC");

	// Create client manager
	manager 	= new ClientManager();

    manager -> addClient(server);
	//manager -> addClient(FILIP_PC);

	//server -> getClient() -> setCallback(mess);
    manager -> setCallbacks(mess);
}

void loop(){
    broker 	-> loop(); /// Broker
    manager -> loop(); /// Clients

    wifi 	-> loop(); /// WiFi connection
}
