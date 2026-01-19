#include <WiFi.h>
#include <WebServer.h>

bool basildi_mi = false;
#define led_pin 2

WebServer server(80);

const char* STA_SSID = "TurkTelekom_ZTYKS3_2.4GHz";
const char* STA_PASS = "x3XuYXczxtYu";


//HTML kodları
String websayfasi = R"rawliteral(
<!DOCTYPE html>
<html>
<body style="text-align:center; font-size:25px;">
  <h1>ESP32 LED TOGGLE</h1>
  <a href="/toggle"><button>LED DURUM DEĞİŞTİR</button></a>
</body>
</html>
)rawliteral";

void handleRoot(){
  server.send(200, "text/html", websayfasi);
}

void ledDeger(){
  basildi_mi = !basildi_mi;//lamba yansın
  server.sendHeader("Location", "/");
  server.send(303);
}


void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID,STA_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleRoot);
  server.on("/toggle", ledDeger);
  server.begin();
  
  Serial.print("SSID :");
  Serial.println(WiFi.localIP());
  Serial.println("Deneyebilirsin");
}

void loop() {
  server.handleClient();

  if(basildi_mi == true){
    digitalWrite(led_pin, HIGH);
    Serial.println("LED Yanıyar 1");

  }else{
    digitalWrite(led_pin, LOW);
    Serial.println("LED Yanmıyah 0");
  }

  delay(500);


}
