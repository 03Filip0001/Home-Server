#ifndef DDNS_HPP
#define DDNS_HPP

#include <HTTPClient.h>

class DDNS{

// "filiman53k  016bb88e5809cedcb9e5380673190629"

protected:

	char *firstPart = "https://api.dynu.com/nic/update?hostname=server-at-home.mywire.org&myip=10.0.0.0&myipv6=no&username=";
	char *middlePart = "&password=";

	char username[128];
	char password[256];

	char request[1024];

	unsigned long lastTime = millis();
	unsigned int SEND_TIME = 60 * 60 * 1000; 

public:
	DDNS(char *username, char* password);

	void send();
	void loop();

};

#endif