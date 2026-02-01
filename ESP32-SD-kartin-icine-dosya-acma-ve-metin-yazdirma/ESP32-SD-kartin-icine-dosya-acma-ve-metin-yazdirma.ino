#include <SPI.h>
#include <SD.h>

#define CS_pin 5


void setup() {
  Serial.begin(115200);

  if(!SD.begin(CS_pin)){
    Serial.println("Sd KArt Bulunamadı");
    return;
  }

  Serial.println("SD Kart Hazır");
  Serial.println("Metin yaz ve 'ENTER' tuşuna bas");

  if(SD.mkdir("/kodla oluşan klasör")){
    Serial.println("Kolasör oluşturuldu");

  }else{
    Serial.println("Kalsör zaten var yada oluşturulamadı");

  }
  


}

void loop() {
  if(Serial.available()){
    String gelen = Serial.readStringUntil('\n');
    gelen.trim();

    File file = SD.open("/kodla oluşan klasör/test5.txt", FILE_APPEND);

    if(!file){
      Serial.println("Dosya Açilamadı");
      return;
    }

    file.println(gelen);
    file.close();

    Serial.println("Kaydedilen Metin: " + gelen);


    //Bir şey denicem
    if(gelen == "Kontrol"){
      File file = SD.open("/kodla oluşan klasör/test5.txt");

      if(!file){
        Serial.println("Dosya Acılamadı");
        return;
      }
      Serial.println("Dosya İçeriği: ");
      while(file.available()){
        char c = file.read();
        Serial.print(c);
      }

      file.close();
    }

  }

}
