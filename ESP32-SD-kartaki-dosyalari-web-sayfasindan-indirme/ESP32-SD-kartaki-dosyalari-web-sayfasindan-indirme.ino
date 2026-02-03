#include <SPI.h>
#include <SD.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

#define CS_pin 5

const char* SSID = "OPPO Reno5 Lite";
const char* PASSWORD = "12345678";

AsyncWebServer server(80);


void setup() {
  Serial.begin(115200);

  if(!SD.begin(CS_pin)){
    Serial.println("SD Kart YOk");
    return;
  }
  Serial.println("SD kart Hazır");

  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/listeleme/index.html", "text/html");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/listeleme/style.css", "text/css");
  });


  server.on("/list", HTTP_GET, [](AsyncWebServerRequest *request){

    File root = SD.open("/");
    
    String html = "<ul>";

    File file = root.openNextFile();

    while(file){
      html += "<li><a href='/download?file=";
      html += file.name();
      html += "'>";
      html += file.name();
      html += "</li>";

      file = root.openNextFile();
    }
    html += "</ul>";

    request->send(200, "text/html", html);

  });

  server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request){

    if(!request->hasParam("file")){
      request->send(400, "test/plain", "Dosyayı Belirtmedin");
      return;
    }

    String filename = request->getParam("file")->value();

    if(!SD.exists("/" + filename)){
      request->send(404, "text/plain", "Dosya Bulunamadı");
      return;
    }

    String contentType = "application/octet-stream";

    if(filename.endsWith(".txt")){
      contentType = "text/plain";
    }
    else if(filename.endsWith(".html")){
      contentType = "text/html";
    }
    else if(filename.endsWith(".css")){
      contentType = "text/css";
    }

    request->send(SD, "/" + filename, contentType);
    
  });

  server.begin();
}

void loop() {

}
