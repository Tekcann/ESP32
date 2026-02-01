#include <SD.h>
#include <SPI.h>

#define CS_pin 5


void setup() {
  Serial.begin(115200);

  //sd akrtı başlatır
  if(!SD.begin(CS_pin)){
    Serial.println("SD KArt başlatılaması");
    return;
  }
  Serial.println("Sd KArt Hazır");


  //dosyayı aç
  File file = SD.open("/deneme.txt.txt");

  if(!file){
    Serial.println("Dosya Bulunamadı");
    return;
  }

  Serial.println("Dosya içeriğii:");



  // Dosyayı oku ve yazdır
  while(file.available()){
    char c = file.read();
    Serial.print(c);
  }
  file.close();

}

void loop() {


}
