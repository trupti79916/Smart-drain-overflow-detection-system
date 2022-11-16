#include <SPI.h>
#include <LoRa.h>

#define SENSOR A5

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  int s_val = analogRead(SENSOR);
  Serial.println(s_val);
  if(s_val > 350){
    Serial.println("Packet Sent:");
    LoRa.beginPacket();
    LoRa.print("1");
    LoRa.endPacket();
  }
}
