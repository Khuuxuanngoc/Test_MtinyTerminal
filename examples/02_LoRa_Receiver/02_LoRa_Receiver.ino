#include <SPI.h>
#include "MKL_LoRa.h"
#include <Wire.h>
#include <MKL_LiquidCrystal_I2C.h>

#define UNO

#ifdef UNO
#define SS_PIN 10
#define RST_PIN 9
#define IO0_PIN 2
#else if ESP
#define SS_PIN 5
#define RST_PIN 13
#define IO0_PIN 14
#endif

MKL_LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

int count = 0;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  LoRa.setPins(SS_PIN, RST_PIN, IO0_PIN);
  while (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    lcd.setCursor(5, 1);
    lcd.print("Failed!");
    delay(500);
  }
  lcd.clear();
}

void loop()
{
  
  lcd.setCursor(0, 0);
  lcd.print("Received: ");
  lcd.setCursor(12, 0);
  lcd.print(count);
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    String str = "";
    // received a packet
    Serial.print("Received packet '");
    // read packet
    while (LoRa.available())
    {
      
      str += (char)LoRa.read();
    }
    Serial.print(str); 
    lcd.setCursor(0, 1);
    lcd.print(str);
    count++;
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
