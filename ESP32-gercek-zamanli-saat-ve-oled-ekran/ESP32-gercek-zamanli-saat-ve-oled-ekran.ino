#include <WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "time.h"

const char* ssid = "Gorkem";//internetin adı
const char* sifre = "grkm1234";//internetin şifresi

const char* saat_verisi_serveri = "pool.ntp.org";//gerçek saat verilerini alacağı yer
const long saat_farki = 3 * 3600;//Türkiye saat farkı UTC +3
const int yaz_saati_farki = 0; 


#define ekran_genislik 128 //ekran genişliği
#define ekran_yukseklik 32 //ekran yüksekliği

#define reset_pin -1 //reset pin yoksa -1 yaz
#define ekran_adres 0x3C //64lü olanlar 0x3D genelde 0x3C

//ekranı hazırlanıyor
Adafruit_SSD1306 display(ekran_genislik, ekran_yukseklik, &Wire, ekran_adres);

void setup() {
  Serial.begin(115200);//haberleşme ağı oluşturuldu
  delay(1000);

 OledHazirlik();//metot çalışır
 WifiHazirlik();

}

void loop() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Saat bilgisi alınamadı!");
    delay(1000);
    return;
  }
 //bu komutları anlamadım
  char zamanStr[50];
  strftime(zamanStr, sizeof(zamanStr), "%d.%m.%Y %H:%M:%S", &timeinfo);

  display.println("Tarih & saat: ");//ekrana yazı
  display.print(zamanStr);//gerçek saat değerini alta

  display.display();

  delay(1000);
  display.clearDisplay();
  display.setCursor(0 ,10);

  
}

void OledHazirlik(){

 Wire.begin(21,22);//sda, sck

   //eğer oled ekranı bulamazsa çalışacak koşul
  if(!display.begin(SSD1306_SWITCHCAPVCC, ekran_adres)){
    Serial.println("Oled Bulunamadı");
    while(true);
  }

 display.clearDisplay();//oled ekranı temizler
 display.setTextSize(1);//yazı boyutunu 2 yapar
 display.setTextColor(SSD1306_WHITE);//yazı rengini beyaz yapar
 display.setCursor(0, 0);//imleci belli bir yere koyar


 display.println("deneme");
  display.display();
}

void WifiHazirlik(){
  
  Serial.print("Wifi'ye bağlanılıyor..."); 
  WiFi.mode(WIFI_STA);//wifinin modunu belirler
  WiFi.begin(ssid, sifre);//wifinin bağlanacağı id ve şifre ile bağlantı kurar

  //bağlanma aşamasında çalışır
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }
  display.clearDisplay();//ekranı temizler 

  Serial.println("\nWiFİ Bağlantısı Başarılı");
  

  //saat ayarlamaları yapılıyor
  configTime(saat_farki, yaz_saati_farki, saat_verisi_serveri);
}
