#include <clev_bot.h>

#define SSID "Casa do Leleco"
#define PASSWORD "3dd91c2b7c"
#define TELEGRAM_TOKEN ""
#define CHAT_ID ""

String cep = "29075910";

int flag = 0;
ClevBot bot(TELEGRAM_TOKEN);

void setup()
{
	Serial.begin(9600);
	delay(10);
	bot.wifi_connect(SSID, PASSWORD);
	bot.set_chat_id(CHAT_ID);
}

void loop()
{
	Serial.println("Testing");
	delay(100);
	if(!flag){
		bot.search_address(cep);
		flag = 1;
	}
	bot.test_receive();
	delay(1000);
}
