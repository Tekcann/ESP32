#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1   // Reset pini yoksa -1
#define SCREEN_ADDRESS 0x3C  // En yaygın I2C adresi

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // I2C başlat
  Wire.begin(21, 22);

  // OLED başlat
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED bulunamadi!");
    while (true);
  }

  display.clearDisplay();

  // Yazı ayarları
  display.setTextSize(1);      // Yazı boyutu (1-2-3...)
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);     // X, Y

  // Yazılar
  display.println("ESP32 OLED");
  display.println("Merhaba Dunya!");
  display.println("128x32 Ekran");

  display.display();  // Ekrana gönder
}

void loop() {
  // Sürekli yazı yazmak istemiyorsak boş
}
