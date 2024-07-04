#include <SPI.h>
#include <Wire.h>
#include <MKL_LiquidCrystal_I2C.h>

#define ESP

#ifdef UNO
#define SS_PIN 10
#define RST_PIN 9
#define IO0_PIN 2
#else if ESP
#define SS_PIN 5
#define RST_PIN 13
#define IO0_PIN 14
#endif

MKL_LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include "MKL_LoRa.h"

int counter = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  Serial.println("LoRa Sender");
  LoRa.setPins(SS_PIN, RST_PIN, IO0_PIN);
  while (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    lcd.setCursor(5, 1);
    lcd.print("LoRa Failed!");
    delay(500);
  }
  lcd.clear();
}

void loop() {
  counter++;
  Serial.print("Sending packet: ");
  Serial.println(counter);

  lcd.setCursor(0, 0);
  lcd.print("Sending: ");
  lcd.setCursor(12, 0);
  lcd.print(counter);
  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  lcd.setCursor(0, 1);
  lcd.print("hello " + String(counter));

  delay(3000);
}
