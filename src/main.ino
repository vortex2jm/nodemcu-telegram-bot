#include <clev_bot.h>

#define SSID "Casa do Leleco"
#define PASSWORD "3dd91c2b7c"
#define TELEGRAM_TOKEN ""
#define CHAT_ID ""

String cep = "29075910";
String message = "",
String last_message = "";
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

	if(last_message == "/start"){
		Serial.println("Coro e coça");
		last_message = "";
	}

  if (bot.got_new_message(message))
  {
    Serial.println(message);
    if(message == "/start"){
      bot.send_start_message();
			last_message = "/start";
    }
  }
  delay(500);
}