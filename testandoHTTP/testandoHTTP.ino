/*
  Comparação das saidas Digitais entre nodeMCU - Arduino
  NodeMCU – Arduino
  D0 = 16;
  D1 = 5;
  D2 = 4;
  D3 = 0;
  D4 = 2; //IR
  D5 = 14;
  D6 = 12;
  D7 = 13;
  D8 = 15;
  D9 = 3;
  D10 = 1;
*/
//Incluindo as bibliotecas necessárias
#include <ESP8266WiFi.h>
// Nome da sua rede Wifi
const char* ssid = "Fabiano";
// Senha da rede
const char* password = "@c5mt-ht9y-9nom@";
// Site que receberá os dados - IMPORTANTE: SEM O HTTP://
const char* host = "192.168.1.40"; //www.site.com.br
void setup() {
  // Iniciando o Serial
  Serial.begin(115200);
  
  // Conectando na rede wifi
  Serial.println("");
  Serial.print("Conectando");
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a rede: ");
  Serial.println(ssid);
}
void loop() {
  // Criando uma conexao TCP
  WiFiClient client;
  const int httpPort = 5000;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  Serial.print("Enviando dado... ");
  // Enviando para o host a temperatura lida.
  client.print(String("GET /sen/0/0") +
                      " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  
  // Repetindo a cada 1 minuto
  Serial.print("Dado enviado: ");
  delay(60000);

}
