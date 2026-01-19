#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

bool basildi_mi = false;
#define led_pin 2

IPAddress localIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

const char* AP_SSID = "ESP32-localBEBY";
const char* AP_PASS = "12345678";

WebServer server(80);
DNSServer dnsServer;

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
  basildi_mi =!basildi_mi;
  server.sendHeader("Location", "/");
  server.send(303);

}



void setup() {
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  WiFi.softAPConfig(localIP, gateway, subnet);

  Serial.println("ESP32 başlatıldı");
  Serial.print("IP adresi :");
  Serial.println(WiFi.softAPIP());

  /*Gelen tüm istekleri ESP32 ye gönderir*/
  /*ANında web sayfasının açılması için gerelkli*/
  dnsServer.start(53, "*", localIP);
  /*53 genel adres- '*' işareti her şey anlamına geliyormuş */
  /*gideceği adres için localIP yi seçtim*/

  server.on("/", handleRoot);
  server.onNotFound(handleRoot);
  server.on("/toggle", ledDeger);
  server.begin();
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

  if(basildi_mi == true){
    digitalWrite(led_pin, HIGH);

  }else{
    digitalWrite(led_pin, LOW);
   
  }

}
