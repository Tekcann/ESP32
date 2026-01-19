#include <WiFi.h>
#include "time.h"


// WiFi bilgileri
const char* ssid = "Gorkem";
const char* password = "grkm1234";

// NTP ayarları
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3 * 3600;   // UTC +3 (Türkiye)
const int   daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // WiFi'ye bağlan
  Serial.print("WiFi'ye bağlanılıyor");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi bağlantısı başarılı!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());

  // Zaman sunucusunu ayarla
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("Zaman sunucusundan saat alınıyor...");
}

void loop() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Saat bilgisi alınamadı!");
    delay(1000);
    return;
  }

  // Saat formatı
  char zamanStr[50];
  strftime(zamanStr, sizeof(zamanStr), "%d.%m.%Y  %H:%M:%S", &timeinfo);

  Serial.print("Tarih & Saat: ");
  Serial.println(zamanStr);

  delay(1000);  // 1 saniyede bir güncelle
}
