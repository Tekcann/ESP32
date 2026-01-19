#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define analog_pin 2

#define ekran_uzunluk 128
#define ekran_yukseklik 32
#define reset_pin -1

#define ekran_adres 0x3C

Adafruit_SSD1306 oled(ekran_uzunluk, ekran_yukseklik, &Wire, reset_pin);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, ekran_adres)) {
    Serial.println("OLED bulunamadi!");
    while (true);
  }
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 10);

  analogReadResolution(12); //0 - 4095 arası değer üretecek 
  analogSetAttenuation(ADC_11db); //0-3.3v arasını ölçeçek



}

void loop() {

  int analog_deger = analogRead(analog_pin);
  int az_deger = map(analog_deger, 0, 4095, 0, ekran_uzunluk);


  oled.println("analog veri :");
  oled.println(analog_deger);
  oled.fillRect(0, 24, az_deger, 8, SSD1306_WHITE);
  oled.display();

  delay(500);

  oled.setCursor(0, 10);
  oled.clearDisplay();

}


