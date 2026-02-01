#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define up_pin  14
#define down_pin 27
#define selected_pin 13
int sayisal_secenek = 0;

#define ekran_uzunluk 128
#define ekran_yukseklik 32
#define reset_pin -1

#define ekran_adres 0X3C

String hangi_secenek = "Boşta";
String sayfa_ismi = "AnaSayfa"; 

Adafruit_SSD1306 oled(ekran_uzunluk,ekran_yukseklik, &Wire, reset_pin);


void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);

  pinMode(up_pin, INPUT_PULLDOWN);
  pinMode(down_pin, INPUT_PULLDOWN);
  pinMode(selected_pin, INPUT_PULLDOWN);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, ekran_adres)) {
    Serial.println("OLED bulunamadi!");
    while (true);
  }

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0,10);
  
}

void loop() {
  int yukari = digitalRead(up_pin);
  int asagi = digitalRead(down_pin);
  

  

  if(yukari == 1){
    sayisal_secenek -= 1;
  }

  else if(asagi == 1){
    sayisal_secenek += 1;
  }
  if(sayisal_secenek > 3 || sayisal_secenek < 0){
    sayisal_secenek = 0;
  }

  switch (sayisal_secenek){

    case 0: // birincş seçenekte olacakla
    hangi_secenek = "Birinci";
    oled.clearDisplay();
    Secenekler();
    oled.setCursor(0, 0);break;

    case 1:
    hangi_secenek = "İkinci";
    oled.clearDisplay();
    Secenekler();
    oled.setCursor(0, 8);break;

    case 2:
    hangi_secenek = "Üçüncü";
    oled.clearDisplay();
    Secenekler();
    oled.setCursor(0, 16);break;

    case 3:
    hangi_secenek = "Dördüncü";
    oled.clearDisplay();
    Secenekler();
    oled.setCursor(0, 24);break;

  }
  SecimKosullari();

  oled.println("*");
  oled.display();
  delay(150);

}

void Secenekler(){
  if(sayfa_ismi == "AnaSayfa"){
  oled.setCursor(15, 0);
  oled.print("Meyveler");

  oled.setCursor(15, 8);
  oled.print("Hayvanlar");

  oled.setCursor(15, 16);
  oled.print("Hocalar");

  oled.setCursor(15, 24);
  oled.print("0Boşta0");

  }
  else if(sayfa_ismi == "Meyveler"){
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

void SecimKosullari(){
  int sec = digitalRead(selected_pin);

  if(sec == 1){


    if(sayfa_ismi == "AnaSayfa"){

      if(hangi_secenek == "Birinci"){
        sayfa_ismi = "Meyveler";
      }
      else if(hangi_secenek == "İkinci"){
        sayfa_ismi = "Hayvanlar";
      }
      else if(hangi_secenek == "Üçüncü"){
        sayfa_ismi = "Hocalar";
      }
      else if(hangi_secenek == "Dördüncü"){
        sayfa_ismi = "21deneme12";
      }
    }

    if(sayfa_ismi == "Meyveler"){
      if(hangi_secenek == "Birinci"){
        sayfa_ismi = "1Boşta1";
      }
      else if(hangi_secenek == "İkinci"){
        sayfa_ismi = "2Boşta2";
      }
      else if(hangi_secenek == "Üçüncü"){
        sayfa_ismi = "3Boşta";
      }
      else if(hangi_secenek == "Dördüncü"){
        sayfa_ismi = "AnaSayfa";
      }
    }

  }

}
