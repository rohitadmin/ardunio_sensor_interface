#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <DHT_U.h>


int counter = 0;
#define dht_1 7
#define DHTTYPE DHT11
DHT dht(dht_1, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) {

    Serial.println("Starting LoRa failed!");

    while (1);

  }
  LoRa.setTxPower(20);
}


void loop() {

  Serial.print("Sending packet: ");
  int temp=dht.readTemperature();
  int hum=dht.readHumidity();
  // send packet
  Serial.print(temp);
  Serial.print(' ');
  Serial.print(hum);
  Serial.println();
  LoRa.beginPacket();
  
  LoRa.print(temp);
  LoRa.print(' ');
  LoRa.print(hum);
  LoRa.endPacket();


  counter++;


  delay(1000);

}
