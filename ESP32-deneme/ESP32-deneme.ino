#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define analog_pin 2
#define buton_pin 5

#define ekran_uzunluk 128
#define ekran_yukseklik 32
#define reset_pin -1

#define ekran_adres 0x3C

const char* hangi_secenek = "Boşta";
const char* sayfa_ismi = "Birinci";

Adafruit_SSD1306 oled(ekran_uzunluk, ekran_yukseklik, &Wire, reset_pin);

void setup() {
  pinMode(buton_pin, INPUT_PULLDOWN);

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

  ButonaBasmaKosullari();

  int analog_deger = analogRead(analog_pin);
  int az_deger = map(analog_deger, 0, 4095, 0, ekran_yukseklik);

  switch (az_deger/8){

  case 0://  0/8 =0
  hangi_secenek = "Birinci";
  oled.clearDisplay();
  Secenekler();
  oled.setCursor(0, 0);break;
  
  case 1://  8/8=1
  hangi_secenek = "İkinci";
  oled.clearDisplay();
  Secenekler();
  oled.setCursor(0, 8);break;

  case 2://  16/8=2
  hangi_secenek = "Üçüncü";
  oled.clearDisplay();
  Secenekler();
  oled.setCursor(0, 16);break;

  case 3://  24/8=3
  hangi_secenek = "Dördüncü";
  oled.clearDisplay();
  Secenekler();
  oled.setCursor(0, 24);break;
  }

  oled.println("*");  
  oled.display();
  delay(500); 
}

void ButonaBasmaKosullari(){
  int buton_durum = digitalRead(buton_pin);

  if(buton_durum == 0){// bu durumda butona basılmış olur
    if(hangi_secenek == "Birinci"){
      sayfa_ismi = "Elmalar";
    }
    else if(hangi_secenek == "Dördüncü"){
      sayfa_ismi = "Birinci";
    }
    
    }
  }
// ekranın yüksekliği 32 pixel harfler 8 pixel 
//her 8 pixelde bir alt kısma geçsin yani 0-8-16-24 dört sıra olacak
//bunu nasıl yaparım
void Secenekler(){
  if(sayfa_ismi == "Birinci"){
  oled.setCursor(15, 0);
  oled.print("1deneme1");

  oled.setCursor(15, 8);
  oled.print("2deneme2");

  oled.setCursor(15, 16);
  oled.print("3deneme3");

  oled.setCursor(15, 24);
  oled.print("4deneme4");
    
  }
  else if(sayfa_ismi = "Elmalar"){
  oled.setCursor(15, 0);
  oled.print("Armut");

  oled.setCursor(15, 8);
  oled.print("Hiyar");

  oled.setCursor(15, 16);
  oled.print("Oteberi");

  oled.setCursor(15, 24);
  oled.print("Geri");  
  }
  

  oled.display();
}
// butona basıldığında hangi case yapısındaysa onun alt basamaklarını yazdırsın



