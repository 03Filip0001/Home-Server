#include "ddns.hpp"

DDNS::DDNS(char* username, char* password){
	strcpy(this -> username, username);
	strcpy(this -> password, password);

	strcpy(this -> request, this -> firstPart);
	strcat(this -> request, this -> username);
	strcat(this -> request, this -> middlePart);
	strcat(this -> request, this -> password);
}

void DDNS::send(){
	HTTPClient http;
    http.begin(this -> request);
    http.end();
    http.GET();
}

void DDNS::loop(){
	if(millis() - lastTime > SEND_TIME){
		this -> send();

		this -> lastTime = millis();
	}
}