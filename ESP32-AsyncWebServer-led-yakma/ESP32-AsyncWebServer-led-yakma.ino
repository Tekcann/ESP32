#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* SSID = "TurkTelekom_ZTYKS3_2.4GHz";
const char* PASSWORD = "x3XuYXczxtYu";

#define led 2


void setup() {
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", 
      "<h2>ESP32 LED Kontrol</h2>"
      "<button onclick=\"fetch('/on')\">ON</button>"
      "<button onclick=\"fetch('/off')\">OFF</button>"
    );
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, HIGH);
    request->send(200, "text/plain", "Led ON");
  });


  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, LOW);
    request->send(200, "text/plain", "led OFF");
  });

  server.begin();

}

void loop() {

}
