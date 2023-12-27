#include "clev_bot.h"
#include <ESP8266WiFi.h>
#include <Arduino_JSON.h>

#define CEP_URL "https://cep.awesomeapi.com.br/json/"

//======================================//
ClevBot::ClevBot(String token) : 
	http(),
	wifiClient(),
	t_bot(token, wifiClient)
{
	this->wifiClient.setInsecure(); // Avoid verifying SSL
}

//=====================================================//
void ClevBot::wifi_connect(String ssid, String password)
{
	Serial.println("Connecting to Wi-Fi");
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		Serial.print(".");
	}
	Serial.println();
	Serial.println("Wifi connected");
}

//=====================================//
void ClevBot::search_address(String cep)
{
	// Testing network connection
	if (this->test_wifi_connection() == 0)
	{
		Serial.println("WiFi is not connected");
		return;
	}

	// Mounting URL
	String url = CEP_URL + cep;
	String payload = "";

	// Doing request
	if (!this->request_get(url, payload))
	{
		Serial.println("Request failure!");
		return;
	}

	// Parsing response
	JSONVar response = JSON.parse(payload);
	if (JSON.typeof(response) == "undefined")
	{
		Serial.println("JSON parsing failure");
		return;
	}

	// Extracting data
	String address = response["address"];
	Serial.println("Response: " + address);
}

//===================================================//
int ClevBot::request_get(String url, String &payload)
{
	this->http.begin(this->wifiClient, url);

	int httpCode = this->http.GET();
	delay(1000);

	if (httpCode > 0)
	{
		payload = this->http.getString();
		this->http.end();
		return 1;
	}

	this->http.end();
	return 0;
}

//=================================//
int ClevBot::test_wifi_connection()
{
	if (WiFi.status() != WL_CONNECTED)
		return 0;
	return 1;
}

//=================================//
void ClevBot::set_chat_id(String id)
{
	this->chat_id = id;
}

void ClevBot::test_receive()
{
	int msg_amount = t_bot.getUpdates(t_bot.last_message_received + 1);
	Serial.println("Entrei na função");
	Serial.println(msg_amount);
	
	while(msg_amount){
		Serial.println("got response");
		for(int x=0; x<msg_amount; x++){
			t_bot.sendMessage(t_bot.messages[x].chat_id, t_bot.messages[x].text, "");
		}
		msg_amount = t_bot.getUpdates(t_bot.last_message_received + 1);
	}
}
