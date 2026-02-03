#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WiFi.h>

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
      "<h2>ESP32 Toggle LED</h2>"
      "<button onclick=\"fetch('/toggle')\">TOGGLE</button>"
     );
  });

  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    bool led_durum = digitalRead(led); //anlık değerini ukurr
    digitalWrite(led, !led_durum); // yanıyorsa söndürür sönukse yakar
    Serial.println("Butona Basıldı");
    Serial.println(led_durum);
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {

}
