#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <time.h>

#include <WebServer.h>
#include <WiFi.h>

String kullanici_metni = "";

#pragma region ekran ayarları

#define ekran_uzunluk 128
#define ekran_yukseklik 32

#define reset_pin -1 //resent pin yoksa -1
#define ekran_adres 0x3C

Adafruit_SSD1306 display(ekran_uzunluk, ekran_yukseklik, &Wire, ekran_adres);

#pragma endregion

#pragma region web ayrları başlangıç

WebServer server(80);


/*AP bilgileri*/ //telefonun esp32 ye bağlanması gerekir
const char* AP_SSID = "ESP32-AYAR 192.168.4.1";
const char* AP_PASS = "12345678";

#pragma endregion

#pragma region saat ayarlamaları
/*NTp saat bilgileri için gerekli */
const char* ntpPerver = "pool.ntp.org";
const long saat_farki = 3*3600;
const int yaz_saat_farki = 0;

#pragma endregion




/* -------- HTML SAYFASI -------- */
String html_AP_sayfasi = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>ESP32 AP Web</title>
</head>
<body>
<h2>ESP32 Metin Gonderme</h2>
<form action="/gonder" method="POST">
  <input name="veri" placeholder="Bir metin gir">
  <button type="submit">Gonder</button>
</form>
</body>
</html>
)rawliteral";


/*SAyfanın başlması için gerekli kodlar (sanırım)*/
void handleRoot(){
  server.send(200, "text/html", html_AP_sayfasi);
}

/*Formdan gelen veriyi oled ekrana yazdırmak için*/
void handleGonder(){
  display.setCursor(0,0);
  display.clearDisplay();
  kullanici_metni = server.arg("veri"); //formdan gelen veri
  display.println("Metnin:");
  display.print(kullanici_metni);
  display.display();

  server.send(200, "text/html", "<h3>Metin Alindi!</h3><a href='/'>Geri Don</a>");
}



void setup() {
  Serial.begin(115200);//baund ayarı yapılıyor

  #pragma region Oled Ekran Setup
  Wire.begin(21,22);//I2C başlat

  //oled başlaması
  if(!display.begin(SSD1306_SWITCHCAPVCC, ekran_adres)){
    Serial.println("Oled Bulunamadı");
    while(true);
  }

  display.clearDisplay();
  

  // Yazı ayarları
  display.setTextSize(1);      // Yazı boyutu (1-2-3...)
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);     // X, Y

  #pragma endregion
 
  WiFi.mode(WIFI_AP);//acces point

  /*Kişisel wifi ağı oluşur*/
  WiFi.softAP(AP_SSID, AP_PASS);

  display.println("Google la gir ve");
  display.println(WiFi.softAPIP());
  display.display();

  /*Web server ayarları sanırım*/
  server.on("/", handleRoot);
  server.on("/gonder", HTTP_POST, handleGonder);

  server.begin();


}

void loop() {
  server.handleClient();


}


