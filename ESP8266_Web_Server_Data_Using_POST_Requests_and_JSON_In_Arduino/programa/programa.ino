#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WebServer server;
uint8_t pin_led = LED_BUILTIN;

char* ssid = "Fabiano";
char* psswd = "@c5mt-ht9y-9nom@";


void setup()
{
    pinMode(LED_BUILTIN, 1);
    WiFi.begin(ssid,psswd);
    Serial.begin(115200);
    
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("IP Address:");
    Serial.print(WiFi.localIP());

    server.on("/",[](){server.send(200,"text/plain", "<h1>Hello World</h1>");});
    server.on("/toggle", toggleLED);
    server.on("/arduino", setPanTilt);
    server.begin();
}

void loop(){

    server.handleClient();
}

void toggleLED(){
    digitalWrite(pin_led, !digitalRead(pin_led));
    server.send(204,"");
}

void setPanTilt(){
    String data = server.arg("plain");
    StaticJsonBuffer<200> jBuffer;
    JsonObject& jObject = jBuffer.parseObject(data);
    String nome = jObject["Usuario"];
    String cargo = jObject["Cargo"];
    String pagina = jObject["Pagina"];
    
//    Serial.println(data);
    Serial.println(nome);
    Serial.println(cargo);
    Serial.println(pagina);
    server.send(204, "");
}
