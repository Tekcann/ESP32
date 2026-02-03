#include <SD.h>
#include <SPI.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#define CS_pin 5
#define led 2

const char* SSID = "TurkTelekom_ZTYKS3_2.4GHz";
const char* PASSWORD = "x3XuYXczxtYu";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  if(!SD.begin(CS_pin)){
    Serial.println("SD kar YOk");
    return;
  }
  Serial.println("Sd KArt HAır");

  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/ledKontrol/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/ledKontrol/style.css", "text/css");
  });

  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, HIGH);
    request->send(200, "text/plain", "ON");
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, LOW);
    request->send(200, "text/plain", "OFF");
  });

  server.begin();

}

void loop() {



}
