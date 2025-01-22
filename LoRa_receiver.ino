#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define LORA_SS 10    
#define LORA_RST 9    
#define LORA_DIO0 2   

void setup() {
  Serial.begin(9600);          
  lcd.begin(16, 2);            
  lcd.backlight();             

  lcd.setCursor(0, 0);        
  lcd.print("LoRa Baslatiliyor");

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {    
    Serial.println("LoRa baslatilamadi!");
    lcd.setCursor(0, 1);      
    lcd.print("Basarisiz!");
    while (1);
  }

  Serial.println("LoRa baslatildi.");
  lcd.setCursor(0, 1);
  lcd.print("Basarili!");
  delay(2000);
  lcd.clear();                 
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String gelenMesaj = "";

    while (LoRa.available()) {
      gelenMesaj += (char)LoRa.read();
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Veri Alindi:");
    lcd.setCursor(0, 1);
    lcd.print(gelenMesaj);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Veri Yok!");
  }

  delay(1000); 
}
