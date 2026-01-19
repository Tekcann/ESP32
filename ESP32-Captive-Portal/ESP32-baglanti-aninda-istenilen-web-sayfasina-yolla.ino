#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

/* ====== AP AYARLARI ====== */
const char* apSSID = "ESP32_PORTAL";
const char* apPassword = "12345678"; // En az 8 karakter

IPAddress localIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

/* ====== DNS & WEB SERVER ====== */
DNSServer dnsServer;
WebServer server(80);

/* ====== HTML SAYFASI ====== */
String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Portal</title>
  <style>
    body {
      font-family: Arial;
      text-align: center;
      margin-top: 40px;
    }
    button {
      font-size: 20px;
      padding: 15px 30px;
    }
  </style>
</head>
<body>
  <h1>ESP32 Kontrol Paneli</h1>
  <p>Wi-Fi'ye basariyla baglandin 🎉</p>
  <button onclick="alert('Buraya LED, röle, ayar vs ekleyebilirsin')">
    Test Butonu
  </button>
</body>
</html>
)rawliteral";

/* ====== HANDLER ====== */
void handleRoot() {
  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  /* WiFi AP MODE */
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSSID, apPassword);
  WiFi.softAPConfig(localIP, gateway, subnet);

  Serial.println("ESP32 AP baslatildi");
  Serial.print("IP adresi: ");
  Serial.println(WiFi.softAPIP());

  /* DNS: TUM ISTEKLER ESP32'YE */
  dnsServer.start(53, "*", localIP);

  /* WEB SERVER */
  server.on("/", handleRoot);
  server.onNotFound(handleRoot); // Her adres ayni sayfaya gider
  server.begin();
}

void loop() {
  dnsServer.processNextRequest(); // Captive portal icin SART
  server.handleClient();          // Web isteklerini isle
}
