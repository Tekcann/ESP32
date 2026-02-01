#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <WebServer.h>

#define CS_pin 5

const char* SSID = "TurkTelekom_ZTYKS3_2.4GHz";
const char* PASSWORD = "x3XuYXczxtYu";

WebServer server(80);

String webSayfasi() {
  return R"rawliteral(
  <html>
  <body>
    <h2>SD Karta Veri Yaz</h2>
    <form action="/kaydet">
      <input type="text" name="veri">
      <input type="submit" value="Gonder">
    </form>
  </body>
  </html>
  )rawliteral";
}

void handleRoot(){
  server.send(200, "text/html", webSayfasi());
}

void handleKaydet(){
  String gelen = server.arg("veri");

  if(!SD.exists("/kodla oluşan klasör")){
    SD.mkdir("/kodla oluşan klasör");
  }

  File file = SD.open("/kodla oluşan klasör/webtest.txt", FILE_APPEND);

  if(!file){
    server.send(200, "text/plain", "Dosya açılamadu");
    return;
  }

  file.println(gelen);
  file.close();

  server.sendHeader("location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  if(!SD.begin(CS_pin)){
    Serial.println("SD kart başlatılamadı");
    return;
  }

  WiFi.begin(SSID, PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("ESP32 internete bağlandı");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/kaydet", handleKaydet);
  server.begin();

}

void loop() {
  server.handleClient();

}
