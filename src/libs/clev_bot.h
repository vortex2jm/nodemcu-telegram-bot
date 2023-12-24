#ifndef CLEV_BOT
#define CLEV_BOT
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

class ClevBot
{
private:
	HTTPClient http;
	WiFiClientSecure wifiClient;
	int ClevBot::request_get(String url, String &payload);

public:
	ClevBot();
	void wifi_connect(String ssid, String password);
	void search_address(String cep);
	int test_wifi_connection();
};

#endif
