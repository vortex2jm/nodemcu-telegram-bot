#include "./libs/clev_bot.h"

#define SSID "Casa do Leleco"
#define PASSWORD "3dd91c2b7c"

String cep = "29075910";

int flag = 0;
ClevBot bot;

void setup()
{
	Serial.begin(9600);
	delay(10);
	bot.wifi_connect(SSID, PASSWORD);
}

void loop()
{
	Serial.println("Testing");
	delay(100);
	if(!flag){
		bot.search_address(cep);
	}
	delay(1000);
}
