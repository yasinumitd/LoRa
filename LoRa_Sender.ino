#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 4      
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

#define LORA_SS 10    
#define LORA_RST 9    
#define LORA_DIO0 2   

void setup() {
  Serial.begin(9600);        
  dht.begin();                 
  Serial.println("DHT11 başlatıldı.");

  Serial.println("LoRa başlatılıyor...");
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {    
    Serial.println("LoRa başlatılamadı!");
    while (1);
  }
  Serial.println("LoRa başlatıldı.");
}

void loop() {
 
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();
 
  if (isnan(nem) || isnan(sicaklik)) {
    Serial.println("DHT11'dan veri okuma hatası!");
    delay(2000); 
    return;
  }

  Serial.print("Nem: ");
  Serial.print(nem);
  Serial.print(" %\t");
  Serial.print("Sıcaklık: ");
  Serial.print(sicaklik);
  Serial.println(" °C");

  String mesaj = "Nem: " + String(nem) + " % | Sıcaklık: " + String(sicaklik) + " °C";
  LoRa.beginPacket();
  LoRa.print(mesaj);
  LoRa.endPacket();

  Serial.println("Veri gönderildi: " + mesaj);

  delay(5000); 
}
