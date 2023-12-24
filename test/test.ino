#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

String ssid = "Casa do Leleco";     // Insira o nome da sua rede Wi-Fi
String password = "3dd91c2b7c";
int flag = 0;
HTTPClient http;
WiFiClientSecure wifiClient;

void do_request();

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println("Connecting to wifi");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  Serial.println("Wifi connected");
}


void loop() {
  Serial.print("Oi eu sou João\n");
  delay(1000);
  if(!flag){
   do_request(); 
  }
  delay(1000);
}


void do_request(){
  String url = "https://cep.awesomeapi.com.br/json/29075910";
  wifiClient.setInsecure();
  http.begin(wifiClient, url);
  int httpCode = http.GET();

  delay(5000);
  
  if (httpCode > 0) {
    String payload = http.getString();

    JSONVar response = JSON.parse(payload);
    if(JSON.typeof(response) == "undefined"){
      Serial.println("JSON parsing failure");
      return;
    }
    
    String address = response["address"];
    
    Serial.println("Resposta: " + address);
  } else {
    Serial.println("Falha na requisição");
  }

  http.end();
  flag = 1;
}
