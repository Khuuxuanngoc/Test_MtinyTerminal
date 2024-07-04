#include <SPI.h>
#include "LoRa.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  while (!Serial)
    ;
  lcd.setCursor(2, 0);
  lcd.print("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    lcd.setCursor(5, 1);
    lcd.print("Failed!");
    while (1)
      ;
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    lcd.setCursor(0, 1);
    lcd.print("Received: ");
    // read packet
    lcd.setCursor(0, 2);
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
      lcd.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
