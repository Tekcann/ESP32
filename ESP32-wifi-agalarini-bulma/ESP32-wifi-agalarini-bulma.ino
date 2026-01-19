#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("WiFi taraması başlıyor...");

  // ESP32'yi WiFi tarama moduna al
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  int ag_sayisi = WiFi.scanNetworks();

  if (ag_sayisi == 0) {
    Serial.println("Hiç WiFi ağı bulunamadı.");
  } else {
    Serial.print(ag_sayisi);
    Serial.println(" adet WiFi ağı bulundu:\n");

    for (int i = 0; i < ag_sayisi; i++) {
      Serial.print(i + 1);
      Serial.print(") ");

      Serial.print("SSID: ");
      Serial.print(WiFi.SSID(i));

      Serial.print(" | Sinyal Gücü (RSSI): ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm");

      Serial.print(" | Kanal: ");
      Serial.print(WiFi.channel(i));

      Serial.print(" | Şifreli mi?: ");
      Serial.println(WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Hayır" : "Evet");

      delay(10);
    }
  }

  Serial.println("\nTarama bitti.");
}

void loop() {
  // Sürekli tarama istemiyorsak boş bırakılır
}
