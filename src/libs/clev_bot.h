#ifndef CLEV_BOT
#define CLEV_BOT
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <UniversalTelegramBot.h>

class ClevBot
{
private:
	HTTPClient http;
	WiFiClientSecure wifiClient;
	UniversalTelegramBot t_bot;
	String chat_id = "";
	int request_get(String url, String &payload);

public:
	ClevBot(String token);
	int test_wifi_connection();
	void set_chat_id(String id);
	void search_address(String cep);
	void wifi_connect(String ssid, String password);
	void test_receive();
};

#endif
