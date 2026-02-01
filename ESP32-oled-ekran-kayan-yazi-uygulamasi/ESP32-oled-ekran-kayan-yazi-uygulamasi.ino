#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define ekran_uzunluk 128
#define ekran_genislik 32
#define reset_pin -1
#define ekran_adres 0X3C

Adafruit_SSD1306 display(ekran_uzunluk, ekran_genislik, &Wire, reset_pin);

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, ekran_adres)) {
    Serial.println("OLED bulunamadi!");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("EYY!!! AHALİ");
  display.println("Yarin Goruşuruk");
  display.display();
  display.startscrollleft(0X00, 0X07);

  /*
  display.startscrollright(0x00, 0x07);
  display.stopscroll();
  display.startscrolldiagright(0x00, 0x07);
  display.startscrolldiagleft(0x00, 0x07);
  */
  
}

void loop() {

}
