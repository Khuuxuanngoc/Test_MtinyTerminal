#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include "LoRa.h"

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  // if (!LoRa.begin(915E6)) {
  //   Serial.println("Starting LoRa failed!");
  //   while (1);
  // }
  //915E6
    while (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(500);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
